#include "gtest_wrapper.h"

#include "file_utils/load_store.h"
#include "file_utils/load_store_row.h"
#include "file_utils/path_utils.h"
#include "logging/logger.h"

#define SCAN_BUILD_ERROR 0

#if SCAN_BUILD_ERROR == 1
struct X {};
void potential_leak(int a)
{
    X* x{new X};

    if (a == 2) {  // aが2ならメモリリーク
        return;
    }

    delete x;
}
#endif

namespace FileUtils {
namespace {

TEST(path_utils, Logger)
{
    auto log_file_org = "ut_data/load_store/logger_org";
    auto log_file_act = "ut_data/load_store/logger_act";

    RemoveFile(log_file_act);

    LOGGER_INIT(log_file_act);
    LOGGER(1);
    LOGGER("xyz", 3, 5);

    auto const dirs = Paths_t{"ut_data/app1",
                              "ut_data/app1/mod1",
                              "ut_data/app1/mod2",
                              "ut_data/app1/mod2/mod2_1",
                              "ut_data/app1/mod2/mod2_2",
                              "ut_data/app2"};

    LOGGER(ToStringPaths(dirs));
    LOGGER(dirs);

    Logging::Logger::Inst().Close();

    auto exp = std::optional<std::vector<std::string>>{LoadFromFile(log_file_org, Load_Strings)};
    ASSERT_TRUE(exp);

    auto act = std::optional<std::vector<std::string>>{LoadFromFile(log_file_act, Load_Strings)};
    ASSERT_TRUE(act);

    ASSERT_EQ(*exp, *act);

    RemoveFile(log_file_act);
}

TEST(path_utils, NotDirs)
{
    {
        auto const dir_in  = Paths_t{"ut_data/app1",
                                    "ut_data/app1/mod1",
                                    "ut_data/app1/mod2",
                                    "ut_data/app1/mod2/mod2_1",
                                    "ut_data/app1/mod2/mod2_2",
                                    "ut_data/app2"};
        auto const dir_act = Paths_t{NotDirs(dir_in)};

        ASSERT_EQ(Paths_t{}, dir_act);
    }
    {
        auto const dir_in  = Paths_t{"ut_data/app1",
                                    "ut_data/app1/notdir",
                                    "ut_data/notdir2",
                                    "ut_data/app1/mod2/mod2_1",
                                    "ut_data/app1/mod2/mod2_2",
                                    "ut_data/app2"};
        auto const dir_act = Paths_t{NotDirs(dir_in)};
        auto const dir_exp = Paths_t{
            "ut_data/app1/notdir",
            "ut_data/notdir2",
        };

        ASSERT_EQ(dir_exp, dir_act);
    }
}

TEST(path_utils, NormalizeLexically)
{
    // こうなるのでNormalizeLexicallyが必要
    ASSERT_EQ(Path_t("a"), Path_t("a"));
    ASSERT_NE(Path_t("a/"), Path_t("a"));
    ASSERT_EQ("a/", Path_t("x/../a/").lexically_normal().string());
    ASSERT_EQ("a", Path_t("x/../a").lexically_normal().string());

    // テストはここから
    ASSERT_EQ("a", NormalizeLexically("x/../a/").string());
    ASSERT_EQ("a", NormalizeLexically("./x/../a/").string());
    ASSERT_EQ("../a", NormalizeLexically(".././x/../a/").string());
    ASSERT_EQ("../a", NormalizeLexically(".././x/../a////").string());
    ASSERT_EQ("../a", NormalizeLexically(".././x/../a/./././").string());

    ASSERT_EQ("a", NormalizeLexically(Path_t("x/../a/")).string());

    ASSERT_EQ(".", NormalizeLexically(Path_t("./")).string());
    ASSERT_EQ(".", NormalizeLexically(Path_t(".")).string());
}

TEST(path_utils, GenFilename2Path)
{
    auto const act_srcs
        = Paths_t{"ut_data/app1/a_1_c.c", "ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.cpp",
                  "ut_data/app1/a_1_cpp.h", "ut_data/app1/a_2_c.C"};

    auto const act = GenFilename2Path(act_srcs);

    auto const exp = Filename2Path_t{
        {"a_1_c.c", "ut_data/app1/a_1_c.c"},         {"a_1_c.h", "ut_data/app1/a_1_c.h"},
        {"a_1_cpp.cpp", "ut_data/app1/a_1_cpp.cpp"}, {"a_1_cpp.h", "ut_data/app1/a_1_cpp.h"},
        {"a_2_c.C", "ut_data/app1/a_2_c.C"},
    };

    ASSERT_EQ(act, exp);
}

TEST(path_utils, AssginSrcsToDirs)
{
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
                                      "ut_data/app1/mod2/mod2_1.cpp",
                                      "ut_data/app1/mod2/mod2_1.hpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                      "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.cpp",
                                      "ut_data/app1/mod2/mod2_2/mod2_2_1.h",
                                      "ut_data/app2/b_1.cpp",
                                      "ut_data/app2/b_1.h"};

        auto const act = AssginSrcsToDirs(exp_dirs, exp_srcs);

        auto const exp = Dirs2Srcs_t{
            {"ut_data/app1",
             {"ut_data/app1/a_1_c.c", "ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.cpp",
              "ut_data/app1/a_1_cpp.h", "ut_data/app1/a_2_c.C", "ut_data/app1/a_2_c.H",
              "ut_data/app1/a_2_cpp.cxx", "ut_data/app1/a_2_cpp.hpp", "ut_data/app1/a_3_cpp.cc"}},
            {"ut_data/app1/mod1",
             {"ut_data/app1/mod1/mod1_1.cpp", "ut_data/app1/mod1/mod1_1.hpp",
              "ut_data/app1/mod1/mod1_2.hpp"}},
            {"ut_data/app1/mod2", {"ut_data/app1/mod2/mod2_1.cpp", "ut_data/app1/mod2/mod2_1.hpp"}},
            {"ut_data/app1/mod2/mod2_1",
             {"ut_data/app1/mod2/mod2_1/mod2_1_1.cpp", "ut_data/app1/mod2/mod2_1/mod2_1_1.h"}},
            {"ut_data/app1/mod2/mod2_2",
             {"ut_data/app1/mod2/mod2_2/mod2_2_1.cpp", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"}},
            {"ut_data/app2", {"ut_data/app2/b_1.cpp", "ut_data/app2/b_1.h"}},
        };

        ASSERT_EQ(act, exp);
    }
    {
        auto const exp_dirs = Paths_t{".", "ut_data/app1/mod1"};
        auto const exp_srcs = Paths_t{"path_utils.cpp", "ut_data/app1/mod1/mod1_1.cpp",
                                      "ut_data/app1/mod1/mod1_1.hpp"};

        auto const act = AssginSrcsToDirs(exp_dirs, exp_srcs);

        auto const exp = Dirs2Srcs_t{
            {".", {"path_utils.cpp"}},
            {"ut_data/app1/mod1", {"ut_data/app1/mod1/mod1_1.cpp", "ut_data/app1/mod1/mod1_1.hpp"}},
        };

        ASSERT_EQ(act, exp);
    }
}

TEST(path_utils, PackageSrcMatcher2)
{
    auto const exp_dirs = Paths_t{"ut_data", "ut_data/app1/mod2", "ut_data/app1/mod2/mod2_1",
                                  "ut_data/app1/mod2/mod2_2", "ut_data/app2"};

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
                                  "ut_data/app1/mod2/mod2_1.cpp",
                                  "ut_data/app1/mod2/mod2_1.hpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                  "ut_data/app1/mod2/mod2_2/mod2_2_1.cpp",
                                  "ut_data/app1/mod2/mod2_2/mod2_2_1.h",
                                  "ut_data/app2/b_1.cpp",
                                  "ut_data/app2/b_1.h"};

    auto const act = AssginSrcsToDirs(exp_dirs, exp_srcs);

    auto const exp = Dirs2Srcs_t{
        {"ut_data",
         {"ut_data/app1/a_1_c.c", "ut_data/app1/a_1_c.h", "ut_data/app1/a_1_cpp.cpp",
          "ut_data/app1/a_1_cpp.h", "ut_data/app1/a_2_c.C", "ut_data/app1/a_2_c.H",
          "ut_data/app1/a_2_cpp.cxx", "ut_data/app1/a_2_cpp.hpp", "ut_data/app1/a_3_cpp.cc",
          "ut_data/app1/mod1/mod1_1.cpp", "ut_data/app1/mod1/mod1_1.hpp",
          "ut_data/app1/mod1/mod1_2.hpp"}},
        {"ut_data/app1", {}},
        {"ut_data/app1/mod2", {"ut_data/app1/mod2/mod2_1.cpp", "ut_data/app1/mod2/mod2_1.hpp"}},
        {"ut_data/app1/mod2/mod2_1",
         {"ut_data/app1/mod2/mod2_1/mod2_1_1.cpp", "ut_data/app1/mod2/mod2_1/mod2_1_1.h"}},
        {"ut_data/app1/mod2/mod2_2",
         {"ut_data/app1/mod2/mod2_2/mod2_2_1.cpp", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"}},
        {"ut_data/app2", {"ut_data/app2/b_1.cpp", "ut_data/app2/b_1.h"}},
    };

    ASSERT_EQ(act, exp);
}

TEST(path_utils, PackageSrcMatcher3)
{
    auto const exp_dirs
        = Paths_t{"ut_data/app1/mod2/mod2_1", "ut_data/app1/mod2/mod2_2", "ut_data/app2"};

    auto const exp_srcs = Paths_t{"ut_data/app1/a_1_c.c",
                                  "ut_data/app1/mod1/mod1_1.cpp",
                                  "ut_data/app1/mod1/mod1_1.hpp",
                                  "ut_data/app1/mod1/mod1_2.hpp",
                                  "ut_data/app1/mod2/mod2_1.cpp",
                                  "ut_data/app1/mod2/mod2_1.hpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.h",
                                  "ut_data/app1/mod2/mod2_2/mod2_2_1.cpp",
                                  "ut_data/app1/mod2/mod2_2/mod2_2_1.h",
                                  "ut_data/app2/b_1.cpp",
                                  "ut_data/app2/b_1.h"};

    auto const act = AssginSrcsToDirs(exp_dirs, exp_srcs);

    auto const exp = Dirs2Srcs_t{
        {"ut_data/app1/mod2/mod2_1",
         {"ut_data/app1/mod2/mod2_1/mod2_1_1.cpp", "ut_data/app1/mod2/mod2_1/mod2_1_1.h"}},
        {"ut_data/app1/mod2/mod2_2",
         {"ut_data/app1/mod2/mod2_2/mod2_2_1.cpp", "ut_data/app1/mod2/mod2_2/mod2_2_1.h"}},
        {"ut_data/app2", {"ut_data/app2/b_1.cpp", "ut_data/app2/b_1.h"}},
        {"no_package",
         {"ut_data/app1/a_1_c.c", "ut_data/app1/mod1/mod1_1.cpp", "ut_data/app1/mod1/mod1_1.hpp",
          "ut_data/app1/mod1/mod1_2.hpp", "ut_data/app1/mod2/mod2_1.cpp",
          "ut_data/app1/mod2/mod2_1.hpp"}},
    };

    ASSERT_EQ(act, exp);
}

TEST(path_utils, ToString_Path)
{
    {
        auto const exp_path = Path_t{"ut_data/app1/a_1_c.c"};
        auto const exp      = std::string{"ut_data/app1/a_1_c.c"};
        auto const act      = ToStringPath(exp_path);

        ASSERT_EQ(act, exp);
    }
    {
        auto const exp_path = Path_t{""};
        auto const exp      = std::string{"\"\""};
        auto const act      = ToStringPath(exp_path);

        ASSERT_EQ(act, exp);
    }
}

TEST(path_utils, ToString_Paths)
{
    auto const exp_srcs = Paths_t{"ut_data/app1/a_1_c.c", "ut_data/app1/mod1/mod1_1.cpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp",
                                  "ut_data/app1/mod2/mod2_1/mod2_1_1.h", "ut_data/app2/b_1.h"};

    auto const exp = std::string{
        "ut_data/app1/a_1_c.c "
        "ut_data/app1/mod1/mod1_1.cpp "
        "ut_data/app1/mod2/mod2_1/mod2_1_1.cpp "
        "ut_data/app1/mod2/mod2_1/mod2_1_1.h "
        "ut_data/app2/b_1.h"};
    auto const act = ToStringPaths(exp_srcs, " ");

    ASSERT_EQ(act, exp);
}
}  // namespace
}  // namespace FileUtils
