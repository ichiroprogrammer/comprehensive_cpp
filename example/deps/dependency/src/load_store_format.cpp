#include <cassert>
#include <iostream>
#include <regex>

#include "file_utils/load_store.h"
#include "load_store_format.h"

namespace Dependency {
namespace {
auto const file_format_dir2srcs = std::string_view{"#dir2srcs"};
auto const file_format_dir      = std::string_view{"#dir"};
auto const file_format_deps     = std::string_view{"#deps"};
auto const file_format_arch     = std::string_view{"#arch"};
}  // namespace

bool StoreToStream(std::ostream& os, FileUtils::Paths_t const& paths)
{
    os << file_format_dir << std::endl;

    using FileUtils::operator<<;
    os << paths << std::endl;

    return true;
}

bool StoreToStream(std::ostream& os, FileUtils::Dirs2Srcs_t const& dirs2srcs)
{
    os << file_format_dir2srcs << std::endl;

    using FileUtils::operator<<;
    os << dirs2srcs << std::endl;

    return true;
}

namespace {

bool is_format_dirs2srcs(std::istream& is)
{
    auto line = std::string{};

    if (std::getline(is, line)) {
        if (line == file_format_dir2srcs) {
            return true;
        }
    }

    return false;
}

FileUtils::Dirs2Srcs_t load_Dirs2Srcs_t(std::istream& is)
{
    static auto const line_sep = std::regex{R"(^\s*$)"};
    static auto const line_dir = std::regex{R"(^([\w/.]+)$)"};
    static auto const line_src = std::regex{R"(^\s+([\w/.]+)$)"};

    auto line      = std::string{};
    auto dir       = FileUtils::Path_t{};
    auto srcs      = FileUtils::Paths_t{};
    auto dirs2srcs = FileUtils::Dirs2Srcs_t{};

    while (std::getline(is, line)) {
        if (auto results = std::smatch{}; std::regex_match(line, results, line_sep)) {
            dirs2srcs[dir].swap(srcs);
        }
        else if (std::regex_match(line, results, line_dir)) {
            dir = results[1].str();
        }
        else if (std::regex_match(line, results, line_src)) {
            srcs.push_back(results[1].str());
        }
        else {
            std::cout << line << std::endl;
            assert(false);
        }
    }

    return dirs2srcs;
}
}  // namespace

std::optional<FileUtils::Dirs2Srcs_t> Load_Dirs2Srcs(std::istream& is)
{
    auto dirs2srcs = FileUtils::Dirs2Srcs_t{};

    if (!is) {
        return std::nullopt;
    }

    if (!is_format_dirs2srcs(is)) {
        return std::nullopt;
    }

    return load_Dirs2Srcs_t(is);
}

namespace {

bool is_format_dirs(std::istream& is)
{
    auto line = std::string{};

    if (std::getline(is, line)) {
        if (line == file_format_dir) {
            return true;
        }
    }

    return false;
}
}  // namespace

std::optional<FileUtils::Paths_t> Load_Paths(std::istream& is)
{
    auto paths = FileUtils::Paths_t{};

    if (!is_format_dirs(is)) {
        return std::nullopt;
    }

    auto line = std::string{};
    while (std::getline(is, line)) {
        paths.emplace_back(FileUtils::Path_t(line));
    }

    return paths;
}

bool StoreToStream(std::ostream& os, DepRels_t const& dep_rels)
{
    os << file_format_deps << std::endl;
    os << dep_rels << std::endl;

    return true;
}

namespace {

bool is_format_deps(std::istream& is)
{
    auto line = std::string{};

    if (std::getline(is, line)) {
        if (line == file_format_deps) {
            return true;
        }
    }

    return false;
}

struct dep_half_t {
    bool               valid{false};
    std::string        from{};
    std::string        to{};
    uint32_t           count{0};
    FileUtils::Paths_t headers{};
};

FileUtils::Paths_t gen_paths(std::string const& paths_str)
{
    auto const sep = std::regex{R"( +)"};
    auto       ret = FileUtils::Paths_t{};

    if (paths_str.size() != 0) {
        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{paths_str.begin(), paths_str.end(), sep, -1};
             it != end; ++it) {
            ret.emplace_back(it->str());
        }
    }

    return ret;
}

dep_half_t get_dep_half(std::smatch const& results)
{
    auto dep_half = dep_half_t{};

    dep_half.valid   = true;
    dep_half.from    = results[1].str();
    dep_half.to      = results[2].str();
    dep_half.count   = std::stoi(results[3].str());
    dep_half.headers = gen_paths(results[4].str());

    return dep_half;
}

DepRelation gen_dep_rel(dep_half_t&& first, dep_half_t&& second)
{
    assert(first.valid);
    assert(second.valid);
    assert(first.from < second.from);

    return DepRelation{first.from,  first.count,  std::move(first.headers),
                       second.from, second.count, std::move(second.headers)};
}

DepRels_t load_DepRelations_t(std::istream& is)
{
    static auto const line_sep = std::regex{R"(^\s*$)"};
    static auto const line_dep = std::regex{R"(^([\w/.-]+) -> ([\w/.-]+) : ([\d]+) *(.*)$)"};

    auto line   = std::string{};
    auto first  = dep_half_t{};
    auto second = dep_half_t{};

    auto dep_rels = DepRels_t{};

    while (std::getline(is, line)) {
        if (auto results = std::smatch{}; std::regex_match(line, results, line_sep)) {
            dep_rels.emplace_back(gen_dep_rel(std::move(first), std::move(second)));

            first.valid  = false;
            second.valid = false;
        }
        else if (std::regex_match(line, results, line_dep)) {
            (!first.valid ? first : second) = get_dep_half(results);
        }
        else {
            assert(false);
        }
    }

    return dep_rels;
}
}  // namespace

std::optional<DepRels_t> Load_DepRels(std::istream& is)
{
    if (!is) {
        return std::nullopt;
    }

    if (!is_format_deps(is)) {
        return std::nullopt;
    }

    return load_DepRelations_t(is);
}

bool StoreToStream(std::ostream& os, Arch_t const& arch)
{
    os << file_format_arch << std::endl;
    os << arch << std::endl;

    return true;
}
}  // namespace Dependency
