#pragma once
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <string>

namespace FileUtils {

using Path_t = std::filesystem::path;
std::string ToStringPath(Path_t const& paths);

using Paths_t = std::list<std::filesystem::path>;

Paths_t              NotDirs(Paths_t const& dirs);
std::string          ToStringPaths(Paths_t const& paths, std::string_view sep = "\n",
                                   std::string_view indent = "");
inline std::ostream& operator<<(std::ostream& os, Paths_t const& paths)
{
    return os << ToStringPaths(paths);
}

// first path:  filename
// second path: pathname
using Filename2Path_t = std::map<Path_t, Path_t>;
Filename2Path_t GenFilename2Path(Paths_t const& paths);

// first  : package name(directory name)
// second : srcs assigned to package
using Dirs2Srcs_t = std::map<Path_t, Paths_t>;

Dirs2Srcs_t          AssginSrcsToDirs(Paths_t const& dirs, Paths_t const& srcs);
std::string          ToStringDirs2Srcs(Dirs2Srcs_t const& dirs2srcs);
inline std::ostream& operator<<(std::ostream& os, Dirs2Srcs_t const& dirs2srcs)
{
    return os << ToStringDirs2Srcs(dirs2srcs);
}

Path_t NormalizeLexically(Path_t const& path);

void RemoveFile(Path_t const& filename);
}  // namespace FileUtils
