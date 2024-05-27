#include "gtest_wrapper.h"

#include "cpp_src.h"

namespace Dependency {
namespace {

TEST(cpp_src, CppSrc)
{
    using FileUtils::Paths_t;

    auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"ut_data/app1"});
    auto const db                   = FileUtils::GenFilename2Path(act_srcs);
    auto const cpp_src              = CppSrc{"ut_data/app1/a_1_c.c", db};

    auto const exp_incs = Paths_t{"ut_data/app1/a_1_c.h",
                                  "ut_data/app1/a_1_cpp.h",
                                  "ut_data/app1/mod1/mod1_1.hpp",
                                  "ut_data/app1/mod1/mod1_2.hpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                  "ut_data/app1/mod2/mod2_2/mod2_2_1.h"};
    ASSERT_EQ(cpp_src.GetIncs(), exp_incs);

    auto const exp_not_found = Paths_t{"stdio.h", "string.h"};
    ASSERT_EQ(cpp_src.GetIncsNotFound(), exp_not_found);

    auto const cpp_src2 = CppSrc{"ut_data/app1/a_1_cpp.h", db};

    auto const exp_incs2 = Paths_t{
        "ut_data/app1/a_1_cpp.h", "ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp",
        "ut_data/app1/mod2/mod2_1/mod2_1_1.h", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"};
    ASSERT_EQ(cpp_src2.GetIncs(), exp_incs2);

    ASSERT_EQ(cpp_src2.GetIncsNotFound(), Paths_t{});

    auto const cpp_src3 = CppSrc{"ut_data/app1/mod1/mod1_2.hpp", db};

    ASSERT_EQ(cpp_src3.GetIncs(), Paths_t{});

    ASSERT_EQ(cpp_src3.GetIncsNotFound(), Paths_t{});
}

TEST(cpp_src, GenCppSrc)
{
    using FileUtils::Paths_t;

    auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"ut_data/app1"});
    auto const db                   = FileUtils::GenFilename2Path(act_srcs);
    auto const srcs
        = Paths_t{"ut_data/app1/a_1_c.c", "ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.cpp"};
    auto const cpp_srcs_act = GenCppSrc(srcs, db);

    ASSERT_EQ(cpp_srcs_act.size(), 3);

    Paths_t const exp_incs[]{
        {"ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.h", "ut_data/app1/mod1/mod1_1.hpp",
         "ut_data/app1/mod1/mod1_2.hpp", "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
         "ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
        {"ut_data/app1/a_1_cpp.h", "ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp",
         "ut_data/app1/mod2/mod2_1/mod2_1_1.h", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
        {},
    };
    Paths_t const exp_not_found[]{
        {"stdio.h", "string.h"},
        {"stdio.h", "string.h"},
        {},
    };

    auto it_exp_srcs      = srcs.cbegin();
    auto it_exp_incs      = std::cbegin(exp_incs);
    auto it_exp_not_found = std::cbegin(exp_not_found);

    for (auto it_act = cpp_srcs_act.cbegin(); it_act != cpp_srcs_act.cend(); ++it_act) {
        ASSERT_EQ(*it_exp_srcs, it_act->Path());
        ASSERT_EQ(*it_exp_incs, it_act->GetIncs());
        ASSERT_EQ(*it_exp_not_found, it_act->GetIncsNotFound());

        ++it_exp_srcs;
        ++it_exp_incs;
        ++it_exp_not_found;
    }

    ASSERT_EQ(it_exp_srcs, srcs.cend());
    ASSERT_EQ(it_exp_incs, std::cend(exp_incs));
    ASSERT_EQ(it_exp_not_found, std::cend(exp_not_found));
}

TEST(cpp_src, operator_equal)
{
    using FileUtils::Paths_t;

    auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"ut_data/app1"});
    auto const db                   = FileUtils::GenFilename2Path(act_srcs);

    auto const cpp_src_0 = CppSrc{"ut_data/app1/a_1_c.c", db};
    auto const cpp_src_1 = CppSrc{"ut_data/app1/a_1_c.c", db};
    auto const cpp_src_2 = CppSrc{"ut_data/app1/a_1_c.h", db};

    ASSERT_EQ(cpp_src_0, cpp_src_0);
    ASSERT_EQ(cpp_src_0, cpp_src_1);
    ASSERT_EQ(cpp_src_1, cpp_src_0);
    ASSERT_NE(cpp_src_0, cpp_src_2);
}

TEST(cpp_src, operator_lt)
{
    using FileUtils::Paths_t;

    auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"ut_data/app1"});
    auto const db                   = FileUtils::GenFilename2Path(act_srcs);

    auto const cpp_src_0 = CppSrc{"ut_data/app1/a_1_c.c", db};
    auto const cpp_src_1 = CppSrc{"ut_data/app1/a_1_c.h", db};

    ASSERT_LT(cpp_src_0, cpp_src_1);
    ASSERT_GT(cpp_src_1, cpp_src_0);
}

TEST(cpp_src, ToString)
{
    using FileUtils::Paths_t;

    auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"ut_data/app1"});
    auto const db                   = FileUtils::GenFilename2Path(act_srcs);
    auto const cpp_src              = CppSrc{"ut_data/app1/a_1_c.c", db};

    auto const exp = std::string_view{
        "file              : a_1_c.c\n"
        "path              : ut_data/app1/a_1_c.c\n"
        "include           : ut_data/app1/a_1_c.h ut_data/app1/a_1_cpp.h "
        "ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp "
        "ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
        "include not found : stdio.h string.h\n"};

    ASSERT_EQ(ToStringCppSrc(cpp_src), exp);
}

TEST(cpp_src, GetCppDirsSrcs)
{
    using FileUtils::Paths_t;

    {
        auto const exp_dirs = Paths_t{"ut_data/app1",
                                      "ut_data/app1/mod1",
                                      "ut_data/app1/mod2",
                                      "ut_data/app1/mod2/mod2_1",
                                      "ut_data/app1/mod2/mod2_2",
                                      "ut_data/app2"};

        auto const exp_srcs = Paths_t{"ut_data/app1/a_1_c.c",
                                      "ut_data/app1/a_1_c.h",
                                      "ut_data/app1/a_1_cpp.cpp",
                                      "ut_data/app1/a_1_cpp.h",
                                      "ut_data/app1/a_2_c.C",
                                      "ut_data/app1/a_2_c.H",
                                      "ut_data/app1/a_2_cpp.cxx",
                                      "ut_data/app1/a_2_cpp.hpp",
                                      "ut_data/app1/a_3_cpp.cc",
                                      "ut_data/app1/mod1/mod1_1.cpp",
                                      "ut_data/app1/mod1/mod1_1.hpp",
                                      "ut_data/app1/mod1/mod1_2.hpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                      "ut_data/app1/mod2/mod2_1.cpp",
                                      "ut_data/app1/mod2/mod2_1.hpp",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.cpp",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.h",
                                      "ut_data/app2/b_1.cpp",
                                      "ut_data/app2/b_1.h"};

        auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"./ut_data/app1", "ut_data/app2///"});

        ASSERT_EQ(act_dirs, exp_dirs);
        ASSERT_EQ(act_srcs, exp_srcs);
    }
    {
        auto const exp_dirs = Paths_t{"ut_data",
                                      "ut_data/app1",
                                      "ut_data/app1/mod1",
                                      "ut_data/app1/mod2",
                                      "ut_data/app1/mod2/mod2_1",
                                      "ut_data/app1/mod2/mod2_2",
                                      "ut_data/app2"};

        auto const exp_srcs             = Paths_t{"ut_data/app1/a_1_c.c",
                                      "ut_data/app1/a_1_c.h",
                                      "ut_data/app1/a_1_cpp.cpp",
                                      "ut_data/app1/a_1_cpp.h",
                                      "ut_data/app1/a_2_c.C",
                                      "ut_data/app1/a_2_c.H",
                                      "ut_data/app1/a_2_cpp.cxx",
                                      "ut_data/app1/a_2_cpp.hpp",
                                      "ut_data/app1/a_3_cpp.cc",
                                      "ut_data/app1/mod1/mod1_1.cpp",
                                      "ut_data/app1/mod1/mod1_1.hpp",
                                      "ut_data/app1/mod1/mod1_2.hpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                      "ut_data/app1/mod2/mod2_1.cpp",
                                      "ut_data/app1/mod2/mod2_1.hpp",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.cpp",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.h",
                                      "ut_data/app2/b_1.cpp",
                                      "ut_data/app2/b_1.h"};
        auto const [act_dirs, act_srcs] = GetCppDirsSrcs({"././ut_data"});

        ASSERT_EQ(act_dirs, exp_dirs);
        ASSERT_EQ(act_srcs, exp_srcs);
    }
}
}  // namespace
}  // namespace Dependency
