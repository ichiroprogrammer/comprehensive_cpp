#pragma once
#include <iostream>
#include <string>
#include <utility>

#include "cpp_src.h"
#include "file_utils/path_utils.h"

namespace Dependency {

class CppDir {
public:
    explicit CppDir(FileUtils::Path_t const& path, CppSrcs_t&& srcs)
        : path_{path}, srcs_{std::move(srcs)}
    {
    }

    FileUtils::Path_t const& Path() const noexcept { return path_; }
    bool                     Contains(FileUtils::Path_t const& inc_path) const noexcept;

    // first  依存するヘッダファイルのインクルード数
    // second 依存するヘッダファイル
    std::pair<uint32_t, FileUtils::Paths_t> DependsOn(CppDir const& cpp_pack) const;
    CppSrcs_t const&                        GetSrcs() const noexcept { return srcs_; }

private:
    FileUtils::Path_t const path_;
    CppSrcs_t const         srcs_;

    friend bool operator==(CppDir const& lhs, CppDir const& rhs) noexcept  = default;
    friend auto operator<=>(CppDir const& lhs, CppDir const& rhs) noexcept = default;
};

using CppDirs_t = std::vector<CppDir>;

CppDirs_t GenCppDirs(FileUtils::Paths_t const& srcs, FileUtils::Filename2Path_t const& db);

std::string          ToStringCppDir(CppDir const& cpp_pack);
inline std::ostream& operator<<(std::ostream& os, CppDir const& dir)
{
    return os << ToStringCppDir(dir);
}
}  // namespace Dependency
