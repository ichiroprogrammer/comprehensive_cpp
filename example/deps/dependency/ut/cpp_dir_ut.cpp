#include "gtest_wrapper.h"

#include "cpp_dir.h"
#include "cpp_src.h"

namespace Dependency {
namespace {

TEST(cpp_dir, GenCppDirs)
{
    using FileUtils::Paths_t;

    auto const [dirs, srcs] = GetCppDirsSrcs({"ut_data/app1", "ut_data/app2///"});
    auto const db           = FileUtils::GenFilename2Path(srcs);
    auto const cpp_dirs     = CppDirs_t{GenCppDirs(srcs, db)};

    auto a_1_cpp = std::find_if(cpp_dirs.begin(), cpp_dirs.end(),
                                [](CppDir const& pkg) { return pkg.Path() == "a_1_cpp.cpp"; });
    ASSERT_NE(a_1_cpp, cpp_dirs.end());

    auto a_1_cpp_h = std::find_if(cpp_dirs.begin(), cpp_dirs.end(),
                                  [](CppDir const& pkg) { return pkg.Path() == "a_1_cpp.h"; });
    ASSERT_NE(a_1_cpp_h, cpp_dirs.end());

    auto mod2_2_1_h = std::find_if(cpp_dirs.begin(), cpp_dirs.end(),
                                   [](CppDir const& pkg) { return pkg.Path() == "mod2_2_1.h"; });
    ASSERT_NE(mod2_2_1_h, cpp_dirs.end());

    auto ret_a_1_cpp = std::pair<uint32_t, Paths_t>{a_1_cpp->DependsOn(*a_1_cpp_h)};
    ASSERT_EQ(0, ret_a_1_cpp.first);

    auto ret_mod2_2_1_h = std::pair<uint32_t, Paths_t>{mod2_2_1_h->DependsOn(*a_1_cpp_h)};
    ASSERT_EQ(1, ret_mod2_2_1_h.first);
}

TEST(cpp_dir, CppDir)
{
    using FileUtils::Paths_t;

    auto const [dirs, srcs]  = GetCppDirsSrcs({"ut_data/app1", "ut_data/app2///"});
    auto const packagae_srcs = FileUtils::AssginSrcsToDirs(dirs, srcs);
    auto const db            = FileUtils::GenFilename2Path(srcs);

    auto mod1 = CppDir{"ut_data/app1/mod1", GenCppSrc(packagae_srcs.at("ut_data/app1/mod1"), db)};
    auto app2 = CppDir{"ut_data/app2", GenCppSrc(packagae_srcs.at("ut_data/app2"), db)};

    ASSERT_TRUE(mod1.Contains("ut_data/app1/mod1/mod1_1.cpp"));
    ASSERT_TRUE(mod1.Contains("ut_data/app1/mod1/mod1_1.hpp"));
    ASSERT_TRUE(mod1.Contains("ut_data/app1/mod1/mod1_2.hpp"));
    ASSERT_FALSE(mod1.Contains("ut_data/app1/mod2/mod2_1.cpp"));

    auto ret_mod1 = std::pair<uint32_t, Paths_t>{mod1.DependsOn(app2)};
    ASSERT_EQ(0, ret_mod1.first);
    ASSERT_EQ(0, ret_mod1.second.size());

    auto ret_app2 = std::pair<uint32_t, Paths_t>{app2.DependsOn(mod1)};
    ASSERT_EQ(4, ret_app2.first);
    ASSERT_EQ((Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"}),
              ret_app2.second);
}

TEST(cpp_dir, operator_eq_tl)
{
    auto const [dirs, srcs]  = GetCppDirsSrcs({"ut_data/app1", "ut_data/app2///"});
    auto const packagae_srcs = FileUtils::AssginSrcsToDirs(dirs, srcs);
    auto const db            = FileUtils::GenFilename2Path(srcs);

    auto mod1_0 = CppDir{"ut_data/app1/mod1", GenCppSrc(packagae_srcs.at("ut_data/app1/mod1"), db)};
    auto mod1_1 = CppDir{"ut_data/app1/mod1", GenCppSrc(packagae_srcs.at("ut_data/app1/mod1"), db)};
    auto app2   = CppDir{"ut_data/app2", GenCppSrc(packagae_srcs.at("ut_data/app2"), db)};

    ASSERT_EQ(mod1_0, mod1_0);
    ASSERT_EQ(mod1_0, mod1_1);
    ASSERT_EQ(mod1_1, mod1_0);

    ASSERT_NE(mod1_0, app2);
    ASSERT_LT(mod1_0, app2);
    ASSERT_GT(app2, mod1_0);
}
}  // namespace
}  // namespace Dependency
