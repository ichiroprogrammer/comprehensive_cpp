#include <algorithm>
#include <sstream>
#include <utility>

#include "file_utils/path_utils.h"

namespace FileUtils {

std::string ToStringPath(Path_t const& path)
{
    auto pn = path.string();

    if (pn.size() == 0) {
        pn = "\"\"";
    }

    return pn;
}

std::string ToStringPaths(Paths_t const& paths, std::string_view sep, std::string_view indent)
{
    auto ss    = std::ostringstream{};
    auto first = true;

    for (auto const& p : paths) {
        if (!std::exchange(first, false)) {
            ss << sep;
        }

        ss << indent << ToStringPath(p);
    }

    return ss.str();
}

std::string ToStringDirs2Srcs(Dirs2Srcs_t const& dirs2srcs)
{
    auto ss    = std::ostringstream{};
    auto first = bool{true};

    for (auto const& pair : dirs2srcs) {
        if (first) {
            first = false;
        }
        else {
            ss << std::endl;
        }

        ss << ToStringPath(pair.first) << std::endl;
        ss << ToStringPaths(pair.second, "\n", "    ") << std::endl;
    }

    return ss.str();
}

Paths_t NotDirs(Paths_t const& dirs)
{
    auto ret = Paths_t{};

    std::copy_if(dirs.cbegin(), dirs.cend(), std::back_inserter(ret),
                 [](auto const& dir) noexcept { return !std::filesystem::is_directory(dir); });

    return ret;
}

Filename2Path_t GenFilename2Path(Paths_t const& paths)
{
    auto ret = Filename2Path_t{};

    for (auto const& p : paths) {
        ret[p.filename()] = p;
    }

    return ret;
}

namespace {
Path_t const current_dir{"."};

size_t match_count(Path_t const& dir, Path_t const& src)
{
    auto const dir_str = dir.string();
    auto const src_str = dir == current_dir ? "./" + src.string() : src.string();

    if (dir_str.size() >= src_str.size()) {
        return 0;
    }

    auto count     = 0U;
    auto count_max = dir_str.size();

    for (; count < count_max; ++count) {
        if (dir_str[count] != src_str[count]) {
            break;
        }
    }

    if (count == count_max && src_str[count] == '/') {
        return count;
    }

    return 0;
}

Path_t select_package(Path_t const& src, Paths_t const& dirs)
{
    Path_t const* best_match{nullptr};
    auto          count_max = 0U;

    for (auto const& dir : dirs) {
        auto count = match_count(dir, src);
        if (count_max < count) {
            best_match = &dir;
            count_max  = count;
        }
    }

    if (best_match == nullptr) {
        return Path_t("no_package");
    }
    else {
        return *best_match;
    }
}

Paths_t gen_parent_dirs(Path_t const dir)
{
    auto ret = Paths_t{};

    for (auto p = dir.parent_path(), pp = p.parent_path(); !p.empty() && p != pp;
         p = pp, pp = p.parent_path()) {
        ret.push_front(p);
    }

    return ret;
}

// a/
//   a0.c
//   b/
//     c/
//       d/
//         d.c
// のようなファイ構造があった場合、
// d2sには a、a/b/c/d が登録され、a/b、a/b/cは登録されていない。
// a/b、a/b/cを埋めるのがpad_parent_dirsである。
void pad_parent_dirs(Paths_t const& dirs, Dirs2Srcs_t& d2s)
{
    for (auto const& dir : dirs) {
        auto parent_found = false;

        for (auto const& p : gen_parent_dirs(dir)) {
            if (!parent_found && d2s.count(p) != 0) {
                parent_found = true;
            }
            else if (parent_found && d2s.count(p) == 0) {
                d2s[p] = Paths_t();
            }
        }
    }
}
}  // namespace

Dirs2Srcs_t AssginSrcsToDirs(Paths_t const& dirs, Paths_t const& srcs)
{
    auto ret      = Dirs2Srcs_t{};
    auto add_dirs = Paths_t{};

    for (auto const& src : srcs) {
        auto dir = select_package(src, dirs);

        if (ret.count(dir) == 0) {
            ret[dir] = Paths_t();
            add_dirs.push_back(dir);
        }
        ret[dir].push_back(src);
    }

    pad_parent_dirs(add_dirs, ret);

    return ret;
}

Path_t NormalizeLexically(Path_t const& path)
{
    // lexically_normalは"a/../b"を"b"にする
    // 最後の'/'を削除
    auto path_lex = Path_t(path.string() + '/').lexically_normal().string();
    path_lex.pop_back();

    if (path_lex.size() == 0) {
        return Path_t(".");
    }
    return path_lex;
}

void RemoveFile(Path_t const& filename)
{
    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename);
    }
}
}  // namespace FileUtils
