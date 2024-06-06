#include <sstream>

#include "gtest_wrapper.h"

#include "dependency/deps_scenario.h"
#include "file_utils/load_store.h"
#include "file_utils/load_store_row.h"

namespace Dependency {
namespace {

TEST(deps_scenario, PkgGenerator)
{
    using FileUtils::Paths_t;

    {
        auto pg  = PkgGenerator{"ut_data/load_store/pkg_org", true, Paths_t{"ut_data/app3/"}, ""};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app1/mod1\n"
            "ut_data/app1/mod2\n"
            "ut_data/app1/mod2/mod2_1\n"
            "ut_data/app1/mod2/mod2_2\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto pg  = PkgGenerator{"ut_data/load_store/pkg_org", false, Paths_t{}, ""};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app1/mod1\n"
            "ut_data/app1/mod2/mod2_1\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, PkgGenerator2)
{
    using FileUtils::Paths_t;

    {
        auto pg  = PkgGenerator{"", false, Paths_t{"ut_data/app1", "ut_data/app2"}, ""};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto pg  = PkgGenerator{"", false, Paths_t{"ut_data/app1", "ut_data/app2"}, "hehe"};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto pg  = PkgGenerator{"", false, Paths_t{"ut_data/app1", "ut_data/app2"}, ".*/app2"};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto pg  = PkgGenerator{"", true, Paths_t{"ut_data/app1", "ut_data/app2"}, ""};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app1/mod1\n"
            "ut_data/app1/mod2\n"
            "ut_data/app1/mod2/mod2_1\n"
            "ut_data/app1/mod2/mod2_2\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto pg  = PkgGenerator{"", true, Paths_t{"ut_data/app1", "ut_data/app2"}, ".*/mod2/.*"};
        auto exp = std::string{
            "#dir\n"
            "ut_data/app1\n"
            "ut_data/app1/mod1\n"
            "ut_data/app1/mod2\n"
            "ut_data/app2\n"};

        auto ss = std::ostringstream{};

        pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }

    auto exception_occured = false;
    try {
        auto pg = PkgGenerator{"", true, Paths_t{"ut_data/app1/a_1_c.c", "ut_data/app2"}, ""};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("ut_data/app1/a_1_c.c not directory", e.what());
    }
    ASSERT_TRUE(exception_occured);
}

TEST(deps_scenario, SrcsGenerator)
{
    using FileUtils::Paths_t;

    {
        auto sg = SrcsGenerator{
            "", true, Paths_t{"ut_data/app1/mod2/mod2_1", "ut_data/app1/mod2/mod2_2"}, ""};

        // clang-format off
        auto exp = std::string {
            "---\n"
            "mod2_1_1.cpp\n"
            "file              : mod2_1_1.cpp\n"
            "path              : ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "include           : \n"
            "include not found : \n"
            "\n"
            "---\n"
            "mod2_1_1.h\n"
            "file              : mod2_1_1.h\n"
            "path              : ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "include           : ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "include not found : a_1_cpp.h\n"
            "\n"
            "---\n"
            "mod2_2_1.cpp\n"
            "file              : mod2_2_1.cpp\n"
            "path              : ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "include           : ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "include not found : a_1_cpp.h\n"
            "\n"
            "---\n"
            "mod2_2_1.h\n"
            "file              : mod2_2_1.h\n"
            "path              : ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "include           : ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "include not found : a_1_cpp.h\n"
            "\n"};
        // clang-format on

        auto ss = std::ostringstream{};

        sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto sg = SrcsGenerator{
            "", true, Paths_t{"ut_data/app1/mod2/mod2_1", "ut_data/app1/mod2/mod2_2"}, ".*/mod2_2"};

        auto exp = std::string{
            "---\n"
            "mod2_1_1.cpp\n"
            "file              : mod2_1_1.cpp\n"
            "path              : ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "include           : \n"
            "include not found : \n"
            "\n"
            "---\n"
            "mod2_1_1.h\n"
            "file              : mod2_1_1.h\n"
            "path              : ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "include           : \n"
            "include not found : mod2_2_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, Pkg2SrcsGenerator)
{
    using FileUtils::Paths_t;

    auto exception_occured = false;

    try {
        auto p2sg
            = Pkg2SrcsGenerator{"ut_data/app1/a_1_c.c", false, false, Paths_t{"ut_data/app3/"}, ""};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("ut_data/app1/a_1_c.c is illegal", e.what());
    }
    ASSERT_TRUE(exception_occured);

    {
        auto p2sg = Pkg2SrcsGenerator{"ut_data/load_store/pkg_org", true, false,
                                      Paths_t{"ut_data/app3/"}, ""};

        auto exp = std::string{
            "#dir2srcs\n"
            "ut_data/app1\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "\n"
            "ut_data/app1/mod1\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_2\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2sg = Pkg2SrcsGenerator{"ut_data/load_store/pkg_org", true, false,
                                      Paths_t{"ut_data/app3/"}, ".*/mod2\\b.*"};

        auto exp = std::string{
            "#dir2srcs\n"
            "ut_data/app1\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2sg = Pkg2SrcsGenerator{"ut_data/load_store/pkg_org", false, false,
                                      Paths_t{"ut_data/app3/"}, ""};

        auto exp = std::string{
            "#dir2srcs\n"
            "ut_data/app1\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2\n"
            "\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2sg = Pkg2SrcsGenerator{"ut_data/load_store/pkg_org", false, false,
                                      Paths_t{"ut_data/app3/"}, "ut_data/app2"};

        auto exp = std::string{
            "#dir2srcs\n"
            "no_package\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"
            "ut_data/app1\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2\n"
            "\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, Pkg2SrcsGenerator2)
{
    using FileUtils::Paths_t;

    {
        auto dirs2srcs_org_str = std::string{
            "#dir2srcs\n"
            "ut_data\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_2\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto p2sg
            = Pkg2SrcsGenerator{"ut_data/load_store/dirs2srcs_org", true, false, Paths_t{}, ""};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(dirs2srcs_org_str, ss.str());
    }
    {
        auto dirs2srcs_org_str = std::string{
            "#dir2srcs\n"
            "ut_data\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1\n"
            "\n"
            "\n"
            "ut_data/app1/mod2\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_2\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto const dirs = Paths_t{"ut_data", "ut_data/app1/mod2", "ut_data/app1/mod2/mod2_1",
                                  "ut_data/app1/mod2/mod2_2", "ut_data/app2"};

        auto p2sg = Pkg2SrcsGenerator{"", false, false, dirs, ""};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(dirs2srcs_org_str, ss.str());
    }
    {
        auto p2sg = Pkg2SrcsGenerator{"", true, false, Paths_t{"ut_data"}, ""};

        auto const exp = std::string{
            "#dir2srcs\n"
            "ut_data/app1\n"
            "    ut_data/app1/a_1_c.c\n"
            "    ut_data/app1/a_1_c.h\n"
            "    ut_data/app1/a_1_cpp.cpp\n"
            "    ut_data/app1/a_1_cpp.h\n"
            "    ut_data/app1/a_2_c.C\n"
            "    ut_data/app1/a_2_c.H\n"
            "    ut_data/app1/a_2_cpp.cxx\n"
            "    ut_data/app1/a_2_cpp.hpp\n"
            "    ut_data/app1/a_3_cpp.cc\n"
            "\n"
            "ut_data/app1/mod1\n"
            "    ut_data/app1/mod1/mod1_1.cpp\n"
            "    ut_data/app1/mod1/mod1_1.hpp\n"
            "    ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2\n"
            "    ut_data/app1/mod2/mod2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1.hpp\n"
            "\n"
            "ut_data/app1/mod2/mod2_1\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.cpp\n"
            "    ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_2\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.cpp\n"
            "    ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app2\n"
            "    ut_data/app2/b_1.cpp\n"
            "    ut_data/app2/b_1.h\n"
            "\n"};

        auto ss = std::ostringstream{};

        p2sg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, Pkg2PkgGenerator)
{
    using FileUtils::Paths_t;

    auto exception_occured = false;
    try {
        auto p2pg
            = Pkg2PkgGenerator{"ut_data/app1/a_1_c.c", false, false, Paths_t{"ut_data/app3/"}, ""};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("ut_data/app1/a_1_c.c is illegal", e.what());
    }
    ASSERT_TRUE(exception_occured);

    {
        auto p2pg = Pkg2PkgGenerator{"ut_data/load_store/pkg_org", true, false,
                                     Paths_t{"ut_data/app3/"}, ""};

        // clang-format off
        auto exp = std::string {
            "#deps\n"
            "ut_data/app1 -> ut_data/app1/mod1 : 6 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "ut_data/app1/mod1 -> ut_data/app1 : 1 ut_data/app1/a_1_cpp.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> ut_data/app1 : 0 \n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2/mod2_1 : 3 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1 : 1 ut_data/app1/a_1_cpp.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2/mod2_2 : 3 ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "ut_data/app1/mod2/mod2_2 -> ut_data/app1 : 2 ut_data/app1/a_1_cpp.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1 : 3 ut_data/app1/a_1_cpp.h ut_data/app1/a_2_cpp.hpp\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2 : 1 ut_data/app1/mod2/mod2_1.hpp\n"
            "ut_data/app1/mod2 -> ut_data/app1/mod1 : 0 \n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2/mod2_1 : 1 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod1 : 2 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2/mod2_2 : 1 ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "ut_data/app1/mod2/mod2_2 -> ut_data/app1/mod1 : 4 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod1 : 4 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app1/mod2/mod2_1 : 0 \n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod2 : 0 \n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app1/mod2/mod2_2 : 0 \n"
            "ut_data/app1/mod2/mod2_2 -> ut_data/app1/mod2 : 0 \n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod2 : 0 \n"
            "\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod2/mod2_2 : 1 ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "ut_data/app1/mod2/mod2_2 -> ut_data/app1/mod2/mod2_1 : 2 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod2/mod2_1 : 2 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"
            "ut_data/app1/mod2/mod2_2 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod2/mod2_2 : 2 ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"};
        // clang-format on

        auto ss = std::ostringstream{};

        p2pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2pg = Pkg2PkgGenerator{"ut_data/load_store/pkg_org", true, false,
                                     Paths_t{"ut_data/app3/"}, ".*/mod2\\b.*"};

        // clang-format off
        auto exp = std::string {
            "#deps\n"
            "ut_data/app1 -> ut_data/app1/mod1 : 12 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "ut_data/app1/mod1 -> ut_data/app1 : 4 ut_data/app1/a_1_cpp.h ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_1.hpp ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1 : 7 ut_data/app1/a_1_cpp.h ut_data/app1/a_2_cpp.hpp ut_data/app1/mod2/mod2_1/mod2_1_1.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod1 : 4 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"};
        // clang-format on

        auto ss = std::ostringstream{};

        p2pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2pg = Pkg2PkgGenerator{"ut_data/load_store/pkg_org", false, false,
                                     Paths_t{"ut_data/app3/"}, ""};

        // clang-format off
        auto exp = std::string {
            "#deps\n"
            "ut_data/app1 -> ut_data/app1/mod1 : 10 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "ut_data/app1/mod1 -> ut_data/app1 : 3 ut_data/app1/a_1_cpp.h ut_data/app1/mod2/mod2_1.hpp ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> ut_data/app1 : 0 \n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2/mod2_1 : 5 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1 : 2 ut_data/app1/a_1_cpp.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1 : 5 ut_data/app1/a_1_cpp.h ut_data/app1/a_2_cpp.hpp ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> ut_data/app1/mod1 : 0 \n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2/mod2_1 : 1 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod1 : 2 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod1 : 4 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app1/mod2/mod2_1 : 0 \n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod2 : 0 \n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod2 : 0 \n"
            "\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app2 : 0 \n"
            "ut_data/app2 -> ut_data/app1/mod2/mod2_1 : 2 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "\n"};
        // clang-format on

        auto ss = std::ostringstream{};

        p2pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
    {
        auto p2pg = Pkg2PkgGenerator{"ut_data/load_store/pkg_org", false, false,
                                     Paths_t{"ut_data/app3/"}, "ut_data/app2"};

        // clang-format off
        auto exp = std::string {
            "#deps\n"
            "no_package -> ut_data/app1 : 5 ut_data/app1/a_1_cpp.h ut_data/app1/a_2_cpp.hpp ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "ut_data/app1 -> no_package : 0 \n"
            "\n"
            "no_package -> ut_data/app1/mod1 : 4 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "ut_data/app1/mod1 -> no_package : 0 \n"
            "\n"
            "no_package -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> no_package : 0 \n"
            "\n"
            "no_package -> ut_data/app1/mod2/mod2_1 : 2 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> no_package : 0 \n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod1 : 10 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "ut_data/app1/mod1 -> ut_data/app1 : 3 ut_data/app1/a_1_cpp.h ut_data/app1/mod2/mod2_1.hpp ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> ut_data/app1 : 0 \n"
            "\n"
            "ut_data/app1 -> ut_data/app1/mod2/mod2_1 : 5 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1 : 2 ut_data/app1/a_1_cpp.h ut_data/app1/mod2/mod2_2/mod2_2_1.h\n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2 : 0 \n"
            "ut_data/app1/mod2 -> ut_data/app1/mod1 : 0 \n"
            "\n"
            "ut_data/app1/mod1 -> ut_data/app1/mod2/mod2_1 : 1 ut_data/app1/mod2/mod2_1/mod2_1_1.h\n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod1 : 2 ut_data/app1/mod1/mod1_1.hpp ut_data/app1/mod1/mod1_2.hpp\n"
            "\n"
            "ut_data/app1/mod2 -> ut_data/app1/mod2/mod2_1 : 0 \n"
            "ut_data/app1/mod2/mod2_1 -> ut_data/app1/mod2 : 0 \n"
            "\n"};
        // clang-format on

        auto ss = std::ostringstream{};

        p2pg.Output(ss);
        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, ArchGenerator)
{
    using FileUtils::Paths_t;

    auto exception_occured = false;
    try {
        auto ag = ArchGenerator{"ut_data/load_store/arch_org"};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("IN-file load error", e.what());
    }
    ASSERT_TRUE(exception_occured);

    {
        auto ag = ArchGenerator{"ut_data/load_store/deps_org"};
        auto ss = std::stringstream{};

        ag.Output(ss);

        auto act = std::optional<std::vector<std::string>>{FileUtils::Load_Strings(ss)};

        auto exp = std::optional<std::vector<std::string>>{
            FileUtils::LoadFromFile("ut_data/load_store/arch_org", FileUtils::Load_Strings)};

        ASSERT_TRUE(exp);

        ASSERT_EQ(*act, *exp);
    }
}

TEST(deps_scenario, Arch2PUmlGenerator)
{
    auto exception_occured = false;
    try {
        auto ag = Arch2PUmlGenerator{"ut_data/load_store/arch_org"};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("IN-file load error", e.what());
    }
    ASSERT_TRUE(exception_occured);

    {
        auto ag = Arch2PUmlGenerator{"ut_data/load_store/deps_org"};
        auto ss = std::stringstream{};

        ag.Output(ss);

        auto exp = std::string{
            "@startuml\n"
            "scale max 730 width\n"
            "rectangle \"app1\" as ut_data___app1 {\n"
            "    rectangle \"mod1\" as ut_data___app1___mod1\n"
            "    rectangle \"mod2\" as ut_data___app1___mod2 {\n"
            "        rectangle \"mod2_1\" as ut_data___app1___mod2___mod2_1\n"
            "        rectangle \"mod2_2\" as ut_data___app1___mod2___mod2_2\n"
            "    }\n"
            "}\n"
            "rectangle \"app2\" as ut_data___app2\n"
            "\n"
            "ut_data___app1 \"2\" -[#orange]-> ut_data___app1___mod1\n"
            "ut_data___app1___mod2___mod2_2 \"1\" -[#orange]-> ut_data___app1\n"
            "ut_data___app2 \"1\" -[#green]-> ut_data___app1\n"
            "ut_data___app1___mod1 \"1\" -[#green]-> ut_data___app1___mod2\n"
            "ut_data___app1___mod1 \"1\" -[#orange]-> ut_data___app1___mod2___mod2_2\n"
            "ut_data___app2 \"2\" -[#green]-> ut_data___app1___mod1\n"
            "ut_data___app1___mod2___mod2_1 \"1\" <-[#red]-> \"2\" ut_data___app1___mod2___mod2_2\n"
            "\n"
            "@enduml\n"};

        ASSERT_EQ(exp, ss.str());
    }
}

TEST(deps_scenario, CyclicGenerator)
{
    auto exception_occured = false;
    try {
        auto cg = CyclicGenerator{"ut_data/load_store/arch_org"};
    }
    catch (std::runtime_error const& e) {
        exception_occured = true;
        ASSERT_STREQ("IN-file load error", e.what());
    }
    ASSERT_TRUE(exception_occured);

    {
        auto cg = CyclicGenerator{"ut_data/load_store/deps_org"};
        auto ss = std::stringstream{};

        ASSERT_FALSE(cg.Output(ss));

        ASSERT_EQ("cyclic dependencies found\n", ss.str());
    }
    {
        auto cg = CyclicGenerator{"ut_data/load_store/deps_org2"};
        auto ss = std::stringstream{};

        ASSERT_TRUE(cg.Output(ss));

        ASSERT_EQ("cyclic dependencies not found\n", ss.str());
    }
}
}  // namespace
}  // namespace Dependency
