#include <cassert>
#include <fstream>
#include <regex>
#include <sstream>
#include <tuple>

#include "cpp_src.h"
#include "lib/nstd.h"

namespace {

FileUtils::Paths_t get_incs(FileUtils::Path_t const& src)
{
    static auto const include_line = std::regex{R"(^\s*#include\s+["<]([\w/.]+)[">](.*))"};

    auto ret  = FileUtils::Paths_t{};
    auto f    = std::ifstream{src};
    auto line = std::string{};

    while (std::getline(f, line)) {
        if (line.size() > 0) {  // CRLF対策
            auto last = --line.end();
            if (*last == '\xa' || *last == '\xd') {
                line.erase(last);
            }
        }

        if (auto results = std::smatch{}; std::regex_match(line, results, include_line)) {
            ret.emplace_back(FileUtils::Path_t(results[1].str()).filename());
        }
    }

    return ret;
}

void get_incs_full(FileUtils::Filename2Path_t const& db, FileUtils::Path_t const& src,
                   FileUtils::Paths_t& incs, FileUtils::Paths_t& not_found, bool sort_uniq)
{
    auto const inc_files = get_incs(src);

    for (auto const& f : inc_files) {
        if (db.count(f) == 0) {
            not_found.push_back(f);
        }
        else {
            auto full_path = db.at(f);
            if (!any_of(
                    incs.cbegin(), incs.cend(),
                    [&full_path](FileUtils::Path_t const& p) noexcept { return p == full_path; })) {
                incs.emplace_back(full_path);
                get_incs_full(db, full_path, incs, not_found, false);
            }
        }
    }

    if (sort_uniq) {
        Nstd::SortUnique(incs);
        Nstd::SortUnique(not_found);
    }
}
}  // namespace

namespace Dependency {

CppSrc::CppSrc(FileUtils::Path_t const& pathname, FileUtils::Filename2Path_t const& db)
    : path_{FileUtils::NormalizeLexically(pathname)},
      filename_{path_.filename()},
      incs_{},
      not_found_{}
{
    get_incs_full(db, pathname, incs_, not_found_, true);
}

CppSrcs_t GenCppSrc(FileUtils::Paths_t const& srcs, FileUtils::Filename2Path_t const& db)
{
    auto ret = CppSrcs_t{};

    for (auto const& src : srcs) {
        ret.emplace_back(CppSrc{src, db});
    }

    return ret;
}

std::string ToStringCppSrc(CppSrc const& cpp_src)
{
    auto ss = std::ostringstream{};

    ss << "file              : " << FileUtils::ToStringPath(cpp_src.Filename()) << std::endl;
    ss << "path              : " << FileUtils::ToStringPath(cpp_src.Path()) << std::endl;
    ss << "include           : " << FileUtils::ToStringPaths(cpp_src.GetIncs(), " ") << std::endl;
    ss << "include not found : " << FileUtils::ToStringPaths(cpp_src.GetIncsNotFound(), " ")
       << std::endl;

    return ss.str();
}

namespace {
constexpr std::string_view target_ext[]{".c", ".h", ".cpp", ".cxx", ".cc", ".hpp", ".hxx", ".tcc"};

bool is_c_or_cpp(std::string ext)
{
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (std::any_of(std::begin(target_ext), std::end(target_ext),
                    [&ext](std::string_view s) noexcept { return s == ext; })) {
        return true;
    }

    return false;
}

FileUtils::Paths_t gen_dirs(FileUtils::Path_t const& top_dir, FileUtils::Paths_t const& srcs)
{
    auto dirs           = FileUtils::Paths_t{top_dir};
    auto const top_dir2 = FileUtils::Path_t{""};  // top_dirが"."の場合、parent_path()は""になる}。

    for (auto const& src : srcs) {
        for (auto dir = src.parent_path(); dir != top_dir && dir != top_dir2;
             dir      = dir.parent_path()) {
            dirs.push_back(dir);
        }
    }

    return dirs;
}

FileUtils::Paths_t find_c_or_cpp_srcs(FileUtils::Path_t const& top_path)
{
    auto srcs = FileUtils::Paths_t{};

    namespace fs = std::filesystem;
    for (fs::path const& p : fs::recursive_directory_iterator{top_path}) {
        if (fs::is_regular_file(p) && is_c_or_cpp(p.extension())) {
            srcs.emplace_back(FileUtils::NormalizeLexically(p));
        }
    }

    return srcs;
}
}  // namespace

std::pair<FileUtils::Paths_t, FileUtils::Paths_t> GetCppDirsSrcs(FileUtils::Paths_t const& dirs)
{
    auto dirs_srcs = FileUtils::Paths_t{};
    auto srcs      = FileUtils::Paths_t{};

    for (auto const& dir : dirs) {
        FileUtils::Path_t const top_path      = FileUtils::NormalizeLexically(dir);
        auto                    sub_srcs      = find_c_or_cpp_srcs(top_path);
        auto                    sub_dirs_srcs = gen_dirs(top_path, sub_srcs);

        Nstd::Concatenate(srcs, std::move(sub_srcs));
        Nstd::Concatenate(dirs_srcs, std::move(sub_dirs_srcs));
    }

    Nstd::SortUnique(srcs);
    Nstd::SortUnique(dirs_srcs);

    return {std::move(dirs_srcs), std::move(srcs)};
}
}  // namespace Dependency
