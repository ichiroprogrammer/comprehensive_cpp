#include "gtest_wrapper.h"

#include "cpp_deps.h"
#include "cpp_dir.h"
#include "cpp_src.h"

namespace Dependency {
namespace {

TEST(cpp_deps, GenDepRels)
{
    using FileUtils::Paths_t;

    auto const [dirs, srcs] = GetCppDirsSrcs({"ut_data/"});
    auto const assign       = FileUtils::AssginSrcsToDirs(dirs, srcs);
    auto const srcs_db      = FileUtils::GenFilename2Path(srcs);

    auto cpp_dirs = CppDirs_t{};

    for (auto const& pair : assign) {
        cpp_dirs.emplace_back(CppDir{pair.first, GenCppSrc(pair.second, srcs_db)});
    }

    auto dep_all = GenDepRels(cpp_dirs);

    auto const app1   = std::string{"ut_data/app1"};
    auto const mod1   = std::string{"ut_data/app1/mod1"};
    auto const mod2_2 = std::string{"ut_data/app1/mod2/mod2_2"};

    {
        auto const app1_mod1 = FindDepRels(dep_all, app1, mod1);
        ASSERT_EQ("ut_data/app1", app1_mod1->PackageA);
        ASSERT_EQ("ut_data/app1/mod1", app1_mod1->PackageB);

        ASSERT_EQ(6, app1_mod1->CountAtoB);
        ASSERT_EQ(1, app1_mod1->CountBtoA);

        auto const app1_mod1_IncsAtoB
            = Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"};

        ASSERT_EQ(app1_mod1_IncsAtoB, app1_mod1->IncsAtoB);
        ASSERT_EQ(Paths_t{"ut_data/app1/a_1_cpp.h"}, app1_mod1->IncsBtoA);
    }
    {
        auto const app1_mod1 = FindDepRels(dep_all, mod1, app1);
        ASSERT_EQ("ut_data/app1", app1_mod1->PackageA);
        ASSERT_EQ("ut_data/app1/mod1", app1_mod1->PackageB);

        ASSERT_EQ(6, app1_mod1->CountAtoB);
        ASSERT_EQ(1, app1_mod1->CountBtoA);

        auto const app1_mod1_IncsAtoB
            = Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"};

        ASSERT_EQ(app1_mod1_IncsAtoB, app1_mod1->IncsAtoB);
        ASSERT_EQ(Paths_t{"ut_data/app1/a_1_cpp.h"}, app1_mod1->IncsBtoA);
    }
    {
        auto const mod1_mod2_2 = FindDepRels(dep_all, mod1, mod2_2);
        ASSERT_EQ("ut_data/app1/mod1", mod1_mod2_2->PackageA);
        ASSERT_EQ("ut_data/app1/mod2/mod2_2", mod1_mod2_2->PackageB);

        ASSERT_EQ(1, mod1_mod2_2->CountAtoB);
        ASSERT_EQ(4, mod1_mod2_2->CountBtoA);

        auto const mod1_mod2_2_IncsAtoB = Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"};

        ASSERT_EQ(mod1_mod2_2_IncsAtoB, mod1_mod2_2->IncsAtoB);
        ASSERT_EQ((Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"}),
                  mod1_mod2_2->IncsBtoA);
    }
    {
        auto const app1_mod2_2 = FindDepRels(dep_all, app1, mod2_2);
        ASSERT_EQ("ut_data/app1", app1_mod2_2->PackageA);
        ASSERT_EQ("ut_data/app1/mod2/mod2_2", app1_mod2_2->PackageB);

        ASSERT_EQ(3, app1_mod2_2->CountAtoB);
        ASSERT_EQ(2, app1_mod2_2->CountBtoA);

        ASSERT_EQ(Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"}, app1_mod2_2->IncsAtoB);

        auto const app1_mod2_2_IncsAtoB = Paths_t{"ut_data/app1/a_1_cpp.h"};
        ASSERT_EQ(app1_mod2_2_IncsAtoB, app1_mod2_2->IncsBtoA);
    }
}
}  // namespace
}  // namespace Dependency
