#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>

#include "arch_pkg.h"  // 実装用ヘッダファイル
// @@@ sample begin 0:0

#include "cpp_deps.h"                  // 実装用ヘッダファイル
#include "cpp_dir.h"                   // 実装用ヘッダファイル
#include "cpp_src.h"                   // 実装用ヘッダファイル
#include "dependency/deps_scenario.h"  // dependencyパッケージからのインポート
#include "file_utils/load_store.h"     // file_utilsパッケージからのインポート
#include "lib/nstd.h"                  // libパッケージからのインポート
// @@@ sample end
#include "load_store_format.h"

namespace Dependency {
namespace {

bool has_error_for_dir(FileUtils::Paths_t const& dirs)
{
    if (dirs.size() == 0) {
        throw std::runtime_error{"need directories to generate package"};
    }

    auto not_dirs = FileUtils::NotDirs(dirs);

    if (not_dirs.size() != 0) {
        throw std::runtime_error{FileUtils::ToStringPaths(not_dirs) + " not directory"};
    }

    return false;
}

FileUtils::Paths_t remove_dirs_match_pattern(FileUtils::Paths_t&& dirs, std::string const& pattern)
{
    if (pattern.size() == 0) {
        return std::move(dirs);
    }

    auto const re_pattern = std::regex{pattern};

    dirs.remove_if([&re_pattern](auto const& d) {
        auto results = std::smatch{};
        auto d_str   = d.string();
        return std::regex_match(d_str, results, re_pattern);
    });

    return std::move(dirs);
}

// first  dirs配下のソースファイルを含むディレクトリ(パッケージ)
// second 上記パッケージに含まれるソースファイル
std::pair<FileUtils::Paths_t, FileUtils::Dirs2Srcs_t> gen_dirs_and_dirs2srcs(
    FileUtils::Paths_t const& dirs, bool recursive, std::string const& pattern)
{
    auto ret      = std::pair<FileUtils::Paths_t, FileUtils::Paths_t>{GetCppDirsSrcs(dirs)};
    auto srcs     = FileUtils::Paths_t{std::move(ret.second)};
    auto dirs_pkg = FileUtils::Paths_t{recursive ? std::move(ret.first) : dirs};

    dirs_pkg = remove_dirs_match_pattern(std::move(dirs_pkg), pattern);

    auto dirs2srcs = FileUtils::Dirs2Srcs_t{FileUtils::AssginSrcsToDirs(dirs_pkg, srcs)};

    return {std::move(dirs_pkg), std::move(dirs2srcs)};
}

FileUtils::Paths_t gen_dirs(FileUtils::Paths_t const& dirs, bool recursive,
                            std::string const& pattern)
{
    auto dirs2srcs = std::pair<FileUtils::Paths_t, FileUtils::Dirs2Srcs_t>{
        gen_dirs_and_dirs2srcs(dirs, recursive, pattern)};

    auto dirs_pkg = FileUtils::Paths_t{std::move(dirs2srcs.first)};
    auto assign   = FileUtils::Dirs2Srcs_t{std::move(dirs2srcs.second)};

    auto ret = FileUtils::Paths_t{};
    for (auto& dir : dirs_pkg) {
        if (assign.count(dir) == 0) {
            std::cout << dir << " not including C++ files" << std::endl;
        }
        else {
            ret.emplace_back(std::move(dir));
        }
    }

    return ret;
}

FileUtils::Paths_t gen_dirs(std::string const& in, bool recursive,
                            FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
{
    auto dirs = FileUtils::Paths_t{};

    if (in.size() != 0) {
        auto ret = std::optional<FileUtils::Paths_t>{FileUtils::LoadFromFile(in, Load_Paths)};
        if (!ret) {
            throw std::runtime_error{in + " is illegal"};
        }
        dirs = std::move(*ret);
    }

    Nstd::Concatenate(dirs, FileUtils::Paths_t(dirs_opt));

    if (has_error_for_dir(dirs)) {
        return dirs;
    }

    return gen_dirs(dirs, recursive, pattern);
}

bool includes(FileUtils::Paths_t const& dirs, FileUtils::Path_t const& dir) noexcept
{
    auto const count
        = std::count_if(dirs.cbegin(), dirs.cend(),
                        [&dir](auto const& dir_in_dirs) noexcept { return dir_in_dirs == dir; });

    return count != 0;
}

FileUtils::Dirs2Srcs_t dirs2srcs_to_src2src(FileUtils::Paths_t const&    dirs_opt,
                                            FileUtils::Dirs2Srcs_t const dirs2srcs, bool recursive)
{
    auto ret = FileUtils::Dirs2Srcs_t{};

    for (auto const& pair : dirs2srcs) {
        for (auto const& src : pair.second) {
            if (recursive) {
                ret.insert(std::make_pair(src.filename(), FileUtils::Paths_t{src}));
            }
            else {
                if (includes(dirs_opt, pair.first)) {
                    auto dir = FileUtils::NormalizeLexically(src.parent_path());

                    if (dir == pair.first) {
                        ret.insert(std::make_pair(src.filename(), FileUtils::Paths_t{src}));
                    }
                }
            }
        }
    }

    return ret;
}

FileUtils::Dirs2Srcs_t gen_dirs2srcs(std::string const& in, bool recursive, bool src_as_pkg,
                                     FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
{
    auto dirs2srcs = FileUtils::Dirs2Srcs_t{};
    auto dirs      = FileUtils::Paths_t{};

    if (in.size() != 0) {
        using FileUtils::LoadFromFile;
        auto ret = std::optional<FileUtils::Dirs2Srcs_t>{LoadFromFile(in, Load_Dirs2Srcs)};

        if (ret) {
            if (dirs_opt.size() != 0) {
                std::cout << "DIRS ignored." << std::endl;
            }

            if (recursive) {
                std::cout << "option \"recursive\" ignored." << std::endl;
            }
            return std::move(*ret);
        }
        else {
            auto ret = std::optional<FileUtils::Paths_t>{LoadFromFile(in, Load_Paths)};

            if (!ret) {
                throw std::runtime_error{in + " is illegal"};
            }
            dirs = std::move(*ret);
        }
    }

    Nstd::Concatenate(dirs, FileUtils::Paths_t(dirs_opt));

    if (has_error_for_dir(dirs)) {
        return dirs2srcs;
    }

    std::pair<FileUtils::Paths_t, FileUtils::Dirs2Srcs_t> ret
        = gen_dirs_and_dirs2srcs(dirs, recursive, pattern);

    auto dirs_pkg = FileUtils::Paths_t{std::move(ret.first)};
    auto assign   = FileUtils::Dirs2Srcs_t{std::move(ret.second)};

    return src_as_pkg ? dirs2srcs_to_src2src(dirs_opt, assign, recursive) : assign;
}

FileUtils::Filename2Path_t gen_src_db(FileUtils::Dirs2Srcs_t const& dir2srcs)
{
    auto srcs = FileUtils::Paths_t{};

    for (auto const& pair : dir2srcs) {
        auto s = pair.second;
        Nstd::Concatenate(srcs, std::move(s));
    }

    return FileUtils::GenFilename2Path(srcs);
}
}  // namespace

PkgGenerator::PkgGenerator(std::string const& in, bool recursive,
                           FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
    : dirs_{gen_dirs(in, recursive, dirs_opt, pattern)}
{
}

bool PkgGenerator::Output(std::ostream& os) const
{
    StoreToStream(os, dirs_);

    return true;
}

SrcsGenerator::SrcsGenerator(std::string const& in, bool recursive,
                             FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
    : dirs_{gen_dirs(in, recursive, dirs_opt, pattern)}
{
}

bool SrcsGenerator::Output(std::ostream& os) const
{
    auto       ret  = std::pair<FileUtils::Paths_t, FileUtils::Paths_t>{GetCppDirsSrcs(dirs_)};
    auto       dirs = FileUtils::Paths_t{std::move(ret.first)};
    auto       srcs = FileUtils::Paths_t{std::move(ret.second)};
    auto const db   = FileUtils::GenFilename2Path(srcs);

    auto cpp_dirs = CppDirs_t{GenCppDirs(srcs, db)};

    for (auto const& d : cpp_dirs) {
        os << "---" << std::endl;
        os << d << std::endl;
    }

    return true;
}

Pkg2SrcsGenerator::Pkg2SrcsGenerator(std::string const& in, bool recursive, bool src_as_pkg,
                                     FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
    : dirs2srcs_{gen_dirs2srcs(in, recursive, src_as_pkg, dirs_opt, pattern)}
{
}

bool Pkg2SrcsGenerator::Output(std::ostream& os) const
{
    StoreToStream(os, dirs2srcs_);

    return true;
}

Pkg2PkgGenerator::Pkg2PkgGenerator(std::string const& in, bool recursive, bool src_as_pkg,
                                   FileUtils::Paths_t const& dirs_opt, std::string const& pattern)
    : dirs2srcs_{gen_dirs2srcs(in, recursive, src_as_pkg, dirs_opt, pattern)}
{
}

bool Pkg2PkgGenerator::Output(std::ostream& os) const
{
    auto cpp_dirs = CppDirs_t{};

    auto const db = gen_src_db(dirs2srcs_);

    for (auto const& pair : dirs2srcs_) {
        cpp_dirs.emplace_back(CppDir{pair.first, GenCppSrc(pair.second, db)});
    }

    DepRels_t const dep_rels = GenDepRels(cpp_dirs);

    StoreToStream(os, dep_rels);

    return true;
}

namespace {
DepRels_t gen_dep_rel(std::string const& in)
{
    if (in.size() == 0) {
        throw std::runtime_error{"IN-file needed"};
    }

    auto ret = std::optional<DepRels_t>{FileUtils::LoadFromFile(in, Load_DepRels)};

    if (!ret) {
        throw std::runtime_error{"IN-file load error"};
    }

    return *ret;
}
}  // namespace

struct ArchGenerator::Impl {
    Impl(DepRels_t&& a_dep_rels) : dep_rels(std::move(a_dep_rels)), arch(ArchPkg::GenArch(dep_rels))
    {
    }
    DepRels_t const dep_rels;
    Arch_t const    arch;
};

ArchGenerator::ArchGenerator(std::string const& in)
    : impl_{std::make_unique<ArchGenerator::Impl>(gen_dep_rel(in))}
{
}

bool ArchGenerator::Output(std::ostream& os) const
{
    StoreToStream(os, impl_->arch);

    return true;
}
ArchGenerator::~ArchGenerator() {}

Arch2PUmlGenerator::Arch2PUmlGenerator(std::string const& in) : ArchGenerator{in} {}

bool Arch2PUmlGenerator::Output(std::ostream& os) const
{
    os << "@startuml" << std::endl;
    os << "scale max 730 width" << std::endl;  // これ以上大きいとpdfにした時に右端が切れる

    os << ToPlantUML_Rectangle(impl_->arch) << std::endl;
    os << std::endl;

    os << ToPlantUML_Rectangle(impl_->arch, impl_->dep_rels) << std::endl;
    os << std::endl;

    os << "@enduml" << std::endl;

    return true;
}

CyclicGenerator::CyclicGenerator(std::string const& in)
    : ArchGenerator{in}, has_cyclic_dep_{HasCyclicDeps(impl_->arch, impl_->dep_rels)}
{
}

bool CyclicGenerator::Output(std::ostream& os) const
{
    os << "cyclic dependencies " << (has_cyclic_dep_ ? "" : "not ") << "found" << std::endl;

    return !has_cyclic_dep_;
}
}  // namespace Dependency
