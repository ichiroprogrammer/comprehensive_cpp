#include <cassert>
#include <sstream>
#include <tuple>

#include "cpp_dir.h"
#include "cpp_src.h"
#include "lib/nstd.h"

namespace Dependency {

bool CppDir::Contains(FileUtils::Path_t const& inc_path) const noexcept
{
    for (auto const& src : srcs_) {
        if (src.Path() == inc_path) {
            return true;
        }
    }

    return false;
}

std::pair<uint32_t, FileUtils::Paths_t> CppDir::DependsOn(CppDir const& cpp_pack) const
{
    auto count = 0U;
    auto incs  = FileUtils::Paths_t{};

    for (auto const& src : srcs_) {
        for (auto const& inc : src.GetIncs()) {
            if (cpp_pack.Contains(inc)) {
                incs.push_back(inc);
                ++count;
            }
        }
    }

    Nstd::SortUnique(incs);

    return {count, std::move(incs)};
}

CppDirs_t GenCppDirs(FileUtils::Paths_t const& srcs, FileUtils::Filename2Path_t const& db)
{
    auto ret = CppDirs_t{};

    for (auto const& src : srcs) {
        auto cpp_src = CppSrc{src, db};
        ret.emplace_back(CppDir{cpp_src.Filename(), {cpp_src}});
    }

    return ret;
}

std::string ToStringCppDir(CppDir const& cpp_pack)
{
    auto ss = std::ostringstream{};

    ss << FileUtils::ToStringPath(cpp_pack.Path()) << std::endl;

    auto first = true;
    for (auto const& src : cpp_pack.GetSrcs()) {
        if (first) {
            first = false;
        }
        else {
            ss << std::endl;
        }
        ss << ToStringCppSrc(src);
    }

    return ss.str();
}
}  // namespace Dependency
