#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <tuple>

#include "cpp_deps.h"
#include "cpp_dir.h"
#include "cpp_src.h"

namespace Dependency {

std::string ToStringDepRel(DepRelation const& rep_rel)
{
    auto ss = std::ostringstream{};

    ss << FileUtils::ToStringPath(rep_rel.PackageA) << " -> "
       << FileUtils::ToStringPath(rep_rel.PackageB) << " : " << rep_rel.CountAtoB << " "
       << FileUtils::ToStringPaths(rep_rel.IncsAtoB, " ") << std::endl;

    ss << FileUtils::ToStringPath(rep_rel.PackageB) << " -> "
       << FileUtils::ToStringPath(rep_rel.PackageA) << " : " << rep_rel.CountBtoA << " "
       << FileUtils::ToStringPaths(rep_rel.IncsBtoA, " ");

    return ss.str();
}

std::string ToStringDepRels(DepRels_t const& dep_rels)
{
    auto ss = std::ostringstream{};

    auto first = true;
    for (auto const& dep : dep_rels) {
        if (!std::exchange(first, false)) {
            ss << std::endl;
        }
        ss << ToStringDepRel(dep) << std::endl;
    }

    return ss.str();
}

namespace {
DepRelation gen_DepRelation(CppDir const& dirA, CppDir const& dirB)
{
    auto a_dep        = std::pair<uint32_t, FileUtils::Paths_t>{dirA.DependsOn(dirB)};
    auto count_from_a = a_dep.first;
    auto incs_from_a  = std::move(a_dep.second);

    auto b_dep        = std::pair<uint32_t, FileUtils::Paths_t>{dirB.DependsOn(dirA)};
    auto count_from_b = b_dep.first;
    auto incs_from_b  = std::move(b_dep.second);

    if (dirA < dirB) {
        return DepRelation{dirA.Path(), count_from_a, std::move(incs_from_a),
                           dirB.Path(), count_from_b, std::move(incs_from_b)};
    }
    else {
        return DepRelation{dirB.Path(), count_from_b, std::move(incs_from_b),
                           dirA.Path(), count_from_a, std::move(incs_from_a)};
    }
}
}  // namespace

Dir2Dir_t GenDir2Dir(std::string dirA, std::string dirB)
{
    return dirA < dirB ? std::make_pair(std::move(dirA), std::move(dirB))
                       : std::make_pair(std::move(dirB), std::move(dirA));
}

DepRels_t GenDepRels(CppDirs_t const& cpp_dirs)
{
    auto ret = DepRels_t{};

    for (auto const& dirA : cpp_dirs) {
        for (auto const& dirB : cpp_dirs) {
            if (dirA <= dirB) {
                continue;
            }
            ret.emplace_back(gen_DepRelation(dirA, dirB));
        }
    }

    ret.sort();

    return ret;
}

DepRels_t::const_iterator FindDepRels(DepRels_t const& dep_rels, std::string const& dirA,
                                      std::string const& dirB) noexcept
{
    assert(dirA != dirB);

    auto dirs = std::minmax(dirA, dirB);

    return std::find_if(dep_rels.cbegin(), dep_rels.cend(), [&dirs](auto const& d) noexcept {
        return d.PackageA == dirs.first && d.PackageB == dirs.second;
    });
}
}  // namespace Dependency
