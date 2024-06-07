#include <cassert>
#include <sstream>

#include "arch_pkg.h"
#include "lib/nstd.h"

namespace Dependency {

void ArchPkg::set_cyclic(ArchPkg const* pkg, bool is_cyclic) const
{
    assert(std::count(depend_on_.cbegin(), depend_on_.cend(), pkg) != 0);
    assert(cyclic_.count(pkg) == 0 || cyclic_[pkg] == is_cyclic);

    cyclic_.insert(std::make_pair(pkg, is_cyclic));
}

bool ArchPkg::is_cyclic(ArchPkgs_t& history, size_t depth) const
{
    if (++depth > max_depth_) {
        std::cerr << "too deep dependency:" << name_ << std::endl;
        return true;
    }

    auto const it = find(history.cbegin(), history.cend(), this);

    if (it != history.cend()) {  // 循環検出
        for (auto it2 = it; it2 != history.cend(); ++it2) {
            auto next = (std::next(it2) == history.cend()) ? it : std::next(it2);
            (*it2)->set_cyclic(*next, true);
        }

        // it == history.cbegin()ならば、一番上からの循環 A->B->C->...->A
        // it != history.cbegin()ならば、上記以外の循環 A->B->C->...->B
        return it == history.cbegin();
    }

    auto gs = Nstd::ScopedGuard{[&history] { history.pop_back(); }};
    history.push_back(this);

    for (ArchPkg const* pkg : depend_on_) {
        if (pkg->is_cyclic(history, depth)) {
            return true;
        }
    }

    return false;
}

bool ArchPkg::IsCyclic(ArchPkg const& pkg) const
{
    if (std::count(depend_on_.cbegin(), depend_on_.cend(), &pkg) == 0) {
        return false;
    }

    if (cyclic_.count(&pkg) == 0) {
        ArchPkgs_t history{this};
        set_cyclic(&pkg, pkg.is_cyclic(history, 0));
    }

    assert(cyclic_.count(&pkg) != 0);

    return cyclic_[&pkg];
}

bool ArchPkg::IsCyclic() const noexcept
{
    for (ArchPkg const* pkg : DependOn()) {
        if (IsCyclic(*pkg)) {
            return true;
        }
    }

    return false;
}

ArchPkg::Map_Path_ArchPkg_t ArchPkg::build_depend_on(DepRelation const&   dep_rel,
                                                     Map_Path_ArchPkg_t&& pkg_all)
{
    auto const a_path = FileUtils::Path_t(dep_rel.PackageA);
    if (pkg_all.count(a_path) == 0) {
        pkg_all.insert(std::make_pair(a_path, std::make_unique<ArchPkg>(a_path)));
    }

    auto const b_path = FileUtils::Path_t(dep_rel.PackageB);
    if (pkg_all.count(b_path) == 0) {
        pkg_all.insert(std::make_pair(b_path, std::make_unique<ArchPkg>(b_path)));
    }

    ArchPkgPtr_t& a_ptr = pkg_all.at(a_path);
    ArchPkgPtr_t& b_ptr = pkg_all.at(b_path);

    if (dep_rel.CountAtoB != 0) {
        a_ptr->depend_on_.push_back(b_ptr.get());
    }
    if (dep_rel.CountBtoA != 0) {
        b_ptr->depend_on_.push_back(a_ptr.get());
    }

    return std::move(pkg_all);
}

Arch_t ArchPkg::build_children(Map_Path_ArchPkg_t&& pkg_all)
{
    auto cache = std::map<FileUtils::Path_t, ArchPkg*>{};
    auto top   = Arch_t{};

    for (auto& [path, pkg] : pkg_all) {  // C++17 style

        auto const parent_name = path.parent_path();
        cache.insert(std::make_pair(path, pkg.get()));

        if (pkg_all.count(parent_name) == 0) {
            top.emplace_back(std::move(pkg));
        }
        else {
            ArchPkg* parent = cache.count(parent_name) != 0 ? cache.at(parent_name)
                                                            : pkg_all.at(parent_name).get();

            pkg->parent_ = parent;
            parent->children_.emplace_back(std::move(pkg));
        }
    }

    return top;
}

Arch_t ArchPkg::GenArch(DepRels_t const& dep_rels)
{
    auto pkg_all = std::map<FileUtils::Path_t, ArchPkgPtr_t>{};

    for (auto const& d : dep_rels) {
        pkg_all = build_depend_on(d, std::move(pkg_all));
    }

    auto top = Arch_t{build_children(std::move(pkg_all))};

    return top;
}

std::string ArchPkg::make_full_name(ArchPkg const& pkg)
{
    if (pkg.Parent()) {
        return make_full_name(*pkg.Parent()) + "/" + pkg.Name();
    }
    else {
        return pkg.Name();
    }
}

ArchPkg const* FindArchPkgByName(Arch_t const& arch, std::string_view pkg_name) noexcept
{
    for (ArchPkgPtr_t const& pkg_ptr : arch) {
        if (pkg_ptr->Name() == pkg_name) {
            return pkg_ptr.get();
        }
        else {
            ArchPkg const* pkg_found = FindArchPkgByName(pkg_ptr->Children(), pkg_name);
            if (pkg_found) {
                return pkg_found;
            }
        }
    }
    return nullptr;
}

ArchPkg const* FindArchPkgByFullName(Arch_t const& arch, std::string_view full_name) noexcept
{
    for (ArchPkgPtr_t const& pkg_ptr : arch) {
        if (pkg_ptr->FullName() == full_name) {
            return pkg_ptr.get();
        }
        else {
            ArchPkg const* pkg_found = FindArchPkgByFullName(pkg_ptr->Children(), full_name);
            if (pkg_found) {
                return pkg_found;
            }
        }
    }
    return nullptr;
}

namespace {

std::string unique_str_name(std::string const& full_name)
{
    auto ret = Nstd::Replace(full_name, "/", "___");
    return Nstd::Replace(ret, "-", "_");
}

std::string_view cyclic_str(ArchPkg const& pkg) noexcept
{
    if (pkg.IsCyclic()) {
        return ":CYCLIC";
    }

    return "";
}

std::string to_string_depend_on(ArchPkg const& pkg_top, uint32_t indent)
{
    auto ss         = std::ostringstream{};
    auto indent_str = std::string(indent, ' ');

    auto first = true;

    for (ArchPkg const* pkg : pkg_top.DependOn()) {
        if (!std::exchange(first, false)) {
            ss << std::endl;
        }

        ss << indent_str << pkg->Name();

        if (pkg_top.IsCyclic(*pkg)) {
            ss << " : CYCLIC";
        }
        else {
            ss << " : STRAIGHT";
        }
    }

    return ss.str();
}

std::string to_string_pkg(ArchPkg const& arch_pkg, uint32_t indent)
{
    static auto const top        = std::string{"TOP"};
    auto              ss         = std::ostringstream{};
    auto              indent_str = std::string(indent, ' ');

    auto package   = "package  :";
    auto full      = "fullname :";
    auto parent    = "parent   :";
    auto children  = "children : {";
    auto depend_on = "depend_on: {";

    constexpr auto next_indent = 4U;

    ss << indent_str << package << arch_pkg.Name() << cyclic_str(arch_pkg) << std::endl;
    ss << indent_str << full << arch_pkg.FullName() << std::endl;
    ss << indent_str << parent << (arch_pkg.Parent() ? arch_pkg.Parent()->Name() : top)
       << std::endl;

    ss << indent_str << depend_on;
    if (arch_pkg.DependOn().size() != 0) {
        ss << std::endl;
        ss << to_string_depend_on(arch_pkg, indent + next_indent) << std::endl;
        ss << indent_str << "}" << std::endl;
    }
    else {
        ss << " }" << std::endl;
    }

    ss << indent_str << children;
    if (arch_pkg.Children().size() != 0) {
        ss << std::endl;
        ss << ToStringArch(arch_pkg.Children(), indent + next_indent) << std::endl;
        ss << indent_str << "}";
    }
    else {
        ss << " }";
    }

    return ss.str();
}
}  // namespace

std::string ToStringArch(Arch_t const& arch, uint32_t indent)
{
    auto ss    = std::ostringstream{};
    auto first = true;

    for (auto const& pkg : arch) {
        if (!std::exchange(first, false)) {
            ss << std::endl << std::endl;
        }
        ss << to_string_pkg(*pkg, indent);
    }

    return ss.str();
}

namespace {
std::string to_pu_rectangle(ArchPkg const& pkg, uint32_t indent)
{
    auto ss         = std::ostringstream{};
    auto indent_str = std::string(indent, ' ');

    ss << indent_str << "rectangle \"" << pkg.Name() << "\" as " << unique_str_name(pkg.FullName());

    if (pkg.Children().size() != 0) {
        ss << " {" << std::endl;
        ss << ToPlantUML_Rectangle(pkg.Children(), indent + 4);
        ss << std::endl << indent_str << "}";
    }

    return ss.str();
}
}  // namespace

std::string ToPlantUML_Rectangle(Arch_t const& arch, uint32_t indent)
{
    auto ss    = std::ostringstream{};
    auto first = true;

    for (auto const& pkg : arch) {
        if (!std::exchange(first, false)) {
            ss << std::endl;
        }
        ss << to_pu_rectangle(*pkg, indent);
    }

    return ss.str();
}

namespace {

// 単方向依存のみ
bool dep_is_cyclic(std::string const& from, std::string const& to, Arch_t const& arch) noexcept
{
    ArchPkg const* pkg_from = FindArchPkgByFullName(arch, from);
    ArchPkg const* pkg_to   = FindArchPkgByFullName(arch, to);

    assert(pkg_from != nullptr);
    assert(pkg_to != nullptr);

    return pkg_from->IsCyclic(*pkg_to);
}

std::string_view pu_link_color(std::string const& from, std::string const& to,
                               Arch_t const& arch) noexcept
{
    return dep_is_cyclic(from, to, arch) ? "orange" : "green";
}

std::string to_pu_rectangle(Arch_t const& arch, DepRelation const& dep_rel)
{
    auto ss = std::ostringstream{};
    auto a  = unique_str_name(dep_rel.PackageA);
    auto b  = unique_str_name(dep_rel.PackageB);

    if (dep_rel.CountAtoB != 0) {
        ss << a << " \"" << dep_rel.CountAtoB << "\" ";
        if (dep_rel.CountBtoA != 0) {
            ss << "<-[#red]-> \"" << dep_rel.CountBtoA << "\" " << b;
        }
        else {
            ss << "-[#" << pu_link_color(dep_rel.PackageA, dep_rel.PackageB, arch) << "]-> " << b;
        }
    }
    else if (dep_rel.CountBtoA != 0) {
        ss << b << " \"" << dep_rel.CountBtoA << "\" -[#"
           << pu_link_color(dep_rel.PackageB, dep_rel.PackageA, arch) << "]-> " << a;
    }

    return ss.str();
}
}  // namespace

bool HasCyclicDeps(Arch_t const& arch, DepRels_t const& dep_rels) noexcept
{
    for (auto const& dep : dep_rels) {
        if (dep.CountAtoB != 0) {
            if (dep.CountBtoA != 0) {
                return true;
            }
            else {
                if (dep_is_cyclic(dep.PackageA, dep.PackageB, arch)) {
                    return true;
                }
            }
        }
        else if (dep.CountBtoA != 0) {
            if (dep_is_cyclic(dep.PackageB, dep.PackageA, arch)) {
                return true;
            }
        }
    }

    return false;
}

std::string ToPlantUML_Rectangle(Arch_t const& arch, DepRels_t const& dep_rels)
{
    auto ss = std::ostringstream{};

    auto first = true;
    for (auto const& d : dep_rels) {
        auto rel_s = to_pu_rectangle(arch, d);

        if (rel_s.size() != 0) {
            if (!std::exchange(first, false)) {
                ss << std::endl;
            }
            ss << rel_s;
        }
    }
    return ss.str();
}
}  // namespace Dependency
