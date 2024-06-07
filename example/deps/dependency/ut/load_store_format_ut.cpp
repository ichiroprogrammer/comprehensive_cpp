#include "gtest_wrapper.h"

#include "file_utils/load_store.h"
#include "file_utils/load_store_row.h"
#include "load_store_format.h"

namespace Dependency {
namespace {

TEST(load_store_format, Paths_t)
{
    using FileUtils::Paths_t;

    auto const pkg_org = std::string{"ut_data/load_store/pkg_org"};
    auto const pkg_act = std::string{"ut_data/load_store/pkg_act"};

    FileUtils::RemoveFile(pkg_act);

    auto const dir_in
        = Paths_t{"ut_data/app1", "ut_data/app1/mod1", "ut_data/app1/mod2/mod2_1", "ut_data/app2"};

    // ディレクトリなのでエラーなはず
    ASSERT_FALSE(FileUtils::StoreToFile("ut_data/app1", dir_in, StoreToStream));

    ASSERT_TRUE(FileUtils::StoreToFile(pkg_act, dir_in, StoreToStream));

    auto dir_out0 = std::optional<Paths_t>{FileUtils::LoadFromFile(pkg_org, Load_Paths)};
    ASSERT_TRUE(dir_out0);

    auto dir_out1 = std::optional<Paths_t>{FileUtils::LoadFromFile(pkg_act, Load_Paths)};
    ASSERT_TRUE(dir_out1);

    ASSERT_EQ(dir_in, *dir_out0);
    ASSERT_EQ(dir_in, *dir_out1);

    FileUtils::RemoveFile(pkg_act);
}

TEST(load_store_format, Dirs2Srcs_t)
{
    auto const dirs2srcs_org = std::string{"ut_data/load_store/dirs2srcs_org"};
    auto const dirs2srcs_act = std::string{"ut_data/load_store/dirs2srcs_act"};

    FileUtils::RemoveFile(dirs2srcs_act);

    const auto dir2srcs_in = FileUtils::Dirs2Srcs_t{
        {"ut_data",
         {"ut_data/app1/a_1_c.c", "ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.cpp",
          "ut_data/app1/a_1_cpp.h", "ut_data/app1/a_2_c.C", "ut_data/app1/a_2_c.H",
          "ut_data/app1/a_2_cpp.cxx", "ut_data/app1/a_2_cpp.hpp", "ut_data/app1/a_3_cpp.cc",
          "ut_data/app1/mod1/mod1_1.cpp", "ut_data/app1/mod1/mod1_1.hpp",
          "ut_data/app1/mod1/mod1_2.hpp"}},
        {"ut_data/app1/mod2", {"ut_data/app1/mod2/mod2_1.cpp", "ut_data/app1/mod2/mod2_1.hpp"}},
        {"ut_data/app1/mod2/mod2_1",
         {"ut_data/app1/mod2/mod2_1/mod2_1_1.cpp", "ut_data/app1/mod2/mod2_1/mod2_1_1.h"}},
        {"ut_data/app1/mod2/mod2_2",
         {"ut_data/app1/mod2/mod2_2/mod2_2_1.cpp", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"}},
        {"ut_data/app2", {"ut_data/app2/b_1.cpp", "ut_data/app2/b_1.h"}},
    };

    // ディレクトリなのでエラーなはず
    ASSERT_FALSE(FileUtils::StoreToFile("ut_data/app1", dir2srcs_in, StoreToStream));

    ASSERT_TRUE(FileUtils::StoreToFile(dirs2srcs_act, dir2srcs_in, StoreToStream));

    auto dir2srcs_out0 = std::optional<FileUtils::Dirs2Srcs_t>{
        FileUtils::LoadFromFile(dirs2srcs_org, Load_Dirs2Srcs)};
    ASSERT_TRUE(dir2srcs_out0);

    auto dir2srcs_out1 = std::optional<FileUtils::Dirs2Srcs_t>{
        FileUtils::LoadFromFile(dirs2srcs_act, Load_Dirs2Srcs)};
    ASSERT_TRUE(dir2srcs_out1);

    ASSERT_EQ(dir2srcs_in, *dir2srcs_out0);
    ASSERT_EQ(dir2srcs_in, *dir2srcs_out1);

    FileUtils::RemoveFile(dirs2srcs_act);
}

namespace {
using FileUtils::Paths_t;

DepRels_t const dep_rels{
    {DepRelation{"ut_data/app1", 2,
                 Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"},
                 "ut_data/app1/mod1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_2", 1,
                 Paths_t{"ut_data/app1/a_1_cpp.h"}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app2", 1,
                 Paths_t{"ut_data/app1/a_2_cpp.hpp"}}},
    {DepRelation{"ut_data/app1/mod1", 1, Paths_t{"ut_data/app1/mod2/mod2_1.hpp"},
                 "ut_data/app1/mod2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 1, Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
                 "ut_data/app1/mod2/mod2_2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 0, Paths_t{}, "ut_data/app2", 2,
                 Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2/mod2_1", 1, Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
                 "ut_data/app1/mod2/mod2_2", 2, Paths_t{"ut_data/app1/mod2/mod2_1/mod2_1_1.h"}}},
    {DepRelation{"ut_data/app1/mod2/mod2_1", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2/mod2_2", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
};
}  // namespace

TEST(load_store_format, DepRels_t)
{
    auto const deps_org = std::string{"ut_data/load_store/deps_org"};
    auto const deps_act = std::string{"ut_data/load_store/deps_act"};

    FileUtils::RemoveFile(deps_act);

    // ディレクトリなのでエラーなはず
    ASSERT_FALSE(FileUtils::StoreToFile("ut_data/app1", dep_rels, StoreToStream));

    ASSERT_TRUE(FileUtils::StoreToFile(deps_act, dep_rels, StoreToStream));

    auto deps_out0 = std::optional<DepRels_t>{FileUtils::LoadFromFile(deps_org, Load_DepRels)};
    ASSERT_TRUE(deps_out0);

    auto exp_it     = dep_rels.cbegin();
    auto exp_it_end = dep_rels.cend();
    auto act_it     = deps_out0->cbegin();

    while (exp_it != exp_it_end) {
        auto exp_str = ToStringDepRel(*exp_it);
        auto act_str = ToStringDepRel(*act_it);
        ASSERT_EQ(exp_str, act_str);
        ASSERT_EQ(exp_it->PackageA, act_it->PackageA);
        ASSERT_EQ(exp_it->CountAtoB, act_it->CountAtoB);
        ASSERT_EQ(exp_it->IncsAtoB, act_it->IncsAtoB);
        ASSERT_EQ(exp_it->PackageB, act_it->PackageB);
        ASSERT_EQ(exp_it->CountBtoA, act_it->CountBtoA);
        ASSERT_EQ(exp_it->IncsBtoA, act_it->IncsBtoA);
        ASSERT_EQ(*exp_it, *act_it);

        ++exp_it;
        ++act_it;
    }
    ASSERT_EQ(dep_rels, *deps_out0);

    auto deps_out1 = std::optional<DepRels_t>{FileUtils::LoadFromFile(deps_act, Load_DepRels)};
    ASSERT_TRUE(deps_out1);

    ASSERT_EQ(dep_rels, *deps_out1);

    FileUtils::RemoveFile(deps_act);
}

TEST(load_store_format, Arch_t)
{
    auto const arch_exp = std::string{"ut_data/load_store/arch_org"};
    auto const arch_act = std::string{"ut_data/load_store/arch_act"};

    FileUtils::RemoveFile(arch_act);

    auto row_exp = std::optional<std::vector<std::string>>{
        FileUtils::LoadFromFile(arch_exp, FileUtils::Load_Strings)};
    ASSERT_TRUE(row_exp);

    auto const arch = ArchPkg::GenArch(dep_rels);
    ASSERT_TRUE(FileUtils::StoreToFile(arch_act, arch, StoreToStream));

    auto row_act = std::optional<std::vector<std::string>>{
        FileUtils::LoadFromFile(arch_act, FileUtils::Load_Strings)};
    ASSERT_TRUE(row_act);

    ASSERT_EQ(row_exp, *row_act);

    FileUtils::RemoveFile(arch_act);
}
}  // namespace
}  // namespace Dependency
