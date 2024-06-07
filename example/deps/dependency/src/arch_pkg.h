#pragma once

#include "cpp_deps.h"
#include "file_utils/path_utils.h"

namespace Dependency {

class ArchPkg;
using ArchPkgPtr_t = std::unique_ptr<ArchPkg>;
using Arch_t       = std::list<ArchPkgPtr_t>;

using ArchPkgs_t = std::vector<ArchPkg const*>;

class ArchPkg {
public:
    explicit ArchPkg(FileUtils::Path_t const& full_name)
        : name_{full_name.filename()}, full_name_{full_name}
    {
    }

    std::string const& Name() const noexcept { return name_; }
    ArchPkg const*     Parent() const noexcept { return parent_; }
    Arch_t const&      Children() const noexcept { return children_; }
    ArchPkgs_t const&  DependOn() const noexcept { return depend_on_; }
    bool               IsCyclic() const noexcept;
    bool               IsCyclic(ArchPkg const& pkg) const;
    std::string const& FullName() const noexcept { return full_name_; }

    ArchPkg(ArchPkg const&)            = delete;
    ArchPkg& operator=(ArchPkg const&) = delete;

    static Arch_t GenArch(DepRels_t const& deps);

private:
    std::string const                      name_;
    std::string const                      full_name_{};
    ArchPkg const*                         parent_{};
    Arch_t                                 children_{};
    ArchPkgs_t                             depend_on_{};
    mutable std::map<ArchPkg const*, bool> cyclic_{};
    static constexpr size_t                max_depth_{12};

    void set_cyclic(ArchPkg const* pkg, bool is_cyclic) const;

    using Map_Path_ArchPkg_t = std::map<FileUtils::Path_t, ArchPkgPtr_t>;
    static Map_Path_ArchPkg_t build_depend_on(DepRelation const&   dep_rel,
                                              Map_Path_ArchPkg_t&& pkg_all);
    static Arch_t             build_children(Map_Path_ArchPkg_t&& pkg_all);
    static std::string        make_full_name(ArchPkg const& pkg);
    bool                      is_cyclic(ArchPkgs_t& history, size_t depth) const;
};

std::string          ToStringArch(Arch_t const& arch, uint32_t indent = 0);
inline std::ostream& operator<<(std::ostream& os, Arch_t const& arch)
{
    return os << ToStringArch(arch);
}

std::string ToPlantUML_Rectangle(Arch_t const& arch, uint32_t indent = 0);
std::string ToPlantUML_Rectangle(Arch_t const& arch, DepRels_t const& dep_rels);
bool        HasCyclicDeps(Arch_t const& arch, DepRels_t const& dep_rels) noexcept;

ArchPkg const* FindArchPkgByName(Arch_t const& arch, std::string_view pkg_name) noexcept;
ArchPkg const* FindArchPkgByFullName(Arch_t const& arch, std::string_view full_name) noexcept;
}  // namespace Dependency
