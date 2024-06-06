#pragma once
#include <vector>

#include "file_utils/path_utils.h"

#include "cpp_deps.h"
#include "cpp_dir.h"

namespace Dependency {

struct DepRelation {
    explicit DepRelation(std::string package_a, uint32_t count_a2b, FileUtils::Paths_t&& incs_a2b,
                         std::string package_b, uint32_t count_b2a, FileUtils::Paths_t&& incs_b2a)
        : PackageA{std::move(package_a)},
          CountAtoB{count_a2b},
          IncsAtoB{std::move(incs_a2b)},
          PackageB{std::move(package_b)},
          CountBtoA{count_b2a},
          IncsBtoA{std::move(incs_b2a)}
    {
    }

    std::string const        PackageA;
    uint32_t const           CountAtoB;
    FileUtils::Paths_t const IncsAtoB;

    std::string const        PackageB;
    uint32_t const           CountBtoA;
    FileUtils::Paths_t const IncsBtoA;
};

using Dir2Dir_t = std::pair<std::string, std::string>;
using DepRels_t = std::list<DepRelation>;

std::string ToStringDepRel(DepRelation const& rep_rel);

bool        operator==(DepRelation const& lhs, DepRelation const& rhs) noexcept;
inline bool operator!=(DepRelation const& lhs, DepRelation const& rhs) noexcept
{
    return !(lhs == rhs);
}
inline bool operator<(DepRelation const& lhs, DepRelation const& rhs) noexcept
{
    return lhs.PackageA != rhs.PackageA ? lhs.PackageA < rhs.PackageA : lhs.PackageB < rhs.PackageB;
}

inline bool operator>(DepRelation const& lhs, DepRelation const& rhs) noexcept { return rhs < lhs; }

inline std::ostream& operator<<(std::ostream& os, DepRelation const& dep_rel)
{
    return os << ToStringDepRel(dep_rel);
}

Dir2Dir_t GenDir2Dir(std::string const& dirA, std::string const& dirB);

std::string          ToStringDepRels(DepRels_t const& dep_rels);
inline std::ostream& operator<<(std::ostream& os, DepRels_t const& dep_rels)
{
    return os << ToStringDepRels(dep_rels);
}

DepRels_t                 GenDepRels(CppDirs_t const& dirs);
DepRels_t::const_iterator FindDepRels(DepRels_t const& dep_rels, std::string const& dirA,
                                      std::string const& dirB) noexcept;
}  // namespace Dependency
