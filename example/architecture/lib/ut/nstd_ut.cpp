#include <filesystem>
#include <list>
#include <ostream>
#include <regex>
#include <string>

#include "gtest_wrapper.h"

#include "lib/nstd.h"

namespace Nstd {
namespace {

TEST(Nstd, ArrayLength)
{
    {
        char const* act[] = {"d", "a", "ab", "bcd"};

        ASSERT_EQ(4, ArrayLength(act));
    }
    {
        std::string const act[] = {"d", "a", "Ab"};

        ASSERT_EQ(3, ArrayLength(act));
    }
}

TEST(Nstd, SortUnique)
{
    {
        auto act = std::vector<std::string>{"d", "a", "ab", "bcd"};

        SortUnique(act);

        ASSERT_EQ((std::vector<std::string>{"a", "ab", "bcd", "d"}), act);
    }
    {
        auto act = std::list<std::filesystem::path>{"d", "a", "Ab", "bcd"};

        SortUnique(act);

        ASSERT_EQ((std::list<std::filesystem::path>{"Ab", "a", "bcd", "d"}), act);
    }
}

TEST(Nstd, Concatenate)
{
    {
        auto act0 = std::vector<std::string>{"d", "a", "ab"};
        auto act1 = std::vector<std::string>{"bcd", "ef"};

        Concatenate(act0, std::move(act1));
        ASSERT_EQ((std::vector<std::string>{"d", "a", "ab", "bcd", "ef"}), act0);
    }
    {
        auto act0 = std::list<std::filesystem::path>{"d", "a", "ab"};
        auto act1 = std::list<std::filesystem::path>{"bcd", "ef"};

        Concatenate(act0, std::move(act1));
        ASSERT_EQ((std::list<std::filesystem::path>{"d", "a", "ab", "bcd", "ef"}), act0);
    }
}

TEST(Nstd, ScopedGuard)
{
    auto s = std::string{"not called"};

    {
        auto sg = ScopedGuard{[&s]() noexcept { s = "called"; }};
        ASSERT_EQ(s, "not called");
    }

    ASSERT_EQ(s, "called");
}

TEST(Nstd, Replace)
{
    {
        auto in  = std::string{"a-b-c-d"};
        auto act = Replace(in, "-", "/");
        ASSERT_EQ(act, "a/b/c/d");
    }
    {
        auto in  = std::string{"a-b-c-d"};
        auto act = Replace(in, "-", "///////");
        ASSERT_EQ(act, "a///////b///////c///////d");
    }
    {
        auto in  = std::string{"a-b-c-d"};
        auto act = Replace(in, "-", "");
        ASSERT_EQ(act, "abcd");
    }
}

TEST(stl_try, exclude)
{
    auto       dirs    = std::list<std::string>{"A", "B", "A/e", "A/e/f", "B/xxx/ef"};
    auto       exclude = std::string{R"(.*/e\b.*)"};
    auto const pattern = std::regex{exclude};

    dirs.remove_if([&pattern](auto const& d) {
        auto results = std::smatch{};
        return std::regex_match(d, results, pattern);
    });

    ASSERT_EQ(dirs, (std::list<std::string>{"A", "B", "B/xxx/ef"}));
}
}  // namespace

namespace Inner_ {
namespace {
class test_class_exits_put_to {};

std::ostream& operator<<(std::ostream& os, test_class_exits_put_to) { return os; }

class test_class_not_exits_put_to {};

TEST(Nstd, exists_put_to_as_member)
{
    static_assert(exists_put_to_as_member_v<bool>);
    static_assert(exists_put_to_as_member_v<char[3]>);
    static_assert(!exists_put_to_as_member_v<std::string>);
    static_assert(!exists_put_to_as_member_v<std::vector<int>>);
    static_assert(exists_put_to_as_member_v<std::vector<int>*>);
    static_assert(!exists_put_to_as_member_v<test_class_exits_put_to>);
    static_assert(!exists_put_to_as_member_v<test_class_not_exits_put_to>);
    static_assert(exists_put_to_as_member_v<test_class_not_exits_put_to[3]>);
    auto oss = std::ostringstream{};
    oss << test_class_exits_put_to{};
}

TEST(Template, exists_put_to_as_non_member)
{
    static_assert(!exists_put_to_as_non_member_v<bool>);
    static_assert(exists_put_to_as_non_member_v<std::string>);
    static_assert(!exists_put_to_as_non_member_v<std::vector<int>>);
    static_assert(!exists_put_to_as_non_member_v<std::vector<int>*>);
    static_assert(exists_put_to_as_non_member_v<test_class_exits_put_to>);
    static_assert(!exists_put_to_as_non_member_v<test_class_not_exits_put_to>);
    static_assert(!exists_put_to_as_non_member_v<test_class_not_exits_put_to[3]>);
}

TEST(Template, exists_put_to_v)
{
    static_assert(exists_put_to_v<bool>);
    static_assert(exists_put_to_v<std::string>);
    static_assert(!exists_put_to_v<std::vector<int>>);
    static_assert(exists_put_to_v<std::vector<int>*>);
    static_assert(exists_put_to_v<test_class_exits_put_to>);
    static_assert(!exists_put_to_v<test_class_not_exits_put_to>);
    static_assert(exists_put_to_v<test_class_not_exits_put_to[3]>);
}

TEST(Template, is_range)
{
    static_assert(is_range_v<std::string>);
    static_assert(!is_range_v<int>);
    static_assert(is_range_v<int const[3]>);
    static_assert(is_range_v<int[3]>);
}
}  // namespace
}  // namespace Inner_

namespace {
TEST(Template, PutTo)
{
    {
        auto oss = std::ostringstream{};
        char c[] = "c3";

        oss << c;
        ASSERT_EQ("c3", oss.str());
    }
    {
        auto oss = std::ostringstream{};
        auto str = std::vector<std::string>{"1", "2", "3"};

        oss << str;
        ASSERT_EQ("1, 2, 3", oss.str());
    }
    {
        auto oss = std::ostringstream{};
        auto p   = std::list<std::filesystem::path>{"1", "2", "3"};

        oss << p;
        ASSERT_EQ("\"1\", \"2\", \"3\"", oss.str());
    }
}
}  // namespace
}  // namespace Nstd
