#pragma once
#include <string>
#include <utility>
#include <vector>

#include "file_utils/path_utils.h"

namespace Dependency {

class CppSrc {
public:
    explicit CppSrc(FileUtils::Path_t const& pathname, FileUtils::Filename2Path_t const& db);
    FileUtils::Paths_t const& GetIncs() const noexcept { return incs_; }
    FileUtils::Paths_t const& GetIncsNotFound() const noexcept { return not_found_; }
    FileUtils::Path_t const&  Filename() const noexcept { return filename_; }
    FileUtils::Path_t const&  Path() const noexcept { return path_; }

private:
    FileUtils::Path_t const path_;
    FileUtils::Path_t const filename_;
    FileUtils::Paths_t      incs_;
    FileUtils::Paths_t      not_found_;

    friend bool operator==(CppSrc const& lhs, CppSrc const& rhs) noexcept  = default;
    friend auto operator<=>(CppSrc const& lhs, CppSrc const& rhs) noexcept = default;
};

using CppSrcs_t = std::vector<CppSrc>;
CppSrcs_t   GenCppSrc(FileUtils::Paths_t const& srcs, FileUtils::Filename2Path_t const& db);
std::string ToStringCppSrc(CppSrc const& cpp_src);
inline std::ostream& operator<<(std::ostream& os, CppSrc const& cpp_src)
{
    return os << ToStringCppSrc(cpp_src);
}

// first  dirs配下のソースファイルを含むディレクトリ
// second dirs配下のソースファイル
std::pair<FileUtils::Paths_t, FileUtils::Paths_t> GetCppDirsSrcs(FileUtils::Paths_t const& dirs);
}  // namespace Dependency
