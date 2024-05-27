#include <algorithm>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

namespace {
// @@@ sample begin 0:0
// [A]
// 下記Accumlateのfor文を
//  * イテレータを使ったfor文を使用したAccumlate2
//  * 範囲for文を使用したAccumlate3
// を作り、それらの単体テストを行え。また、その時にその他の不具合があれば合わせて修正せよ。

std::string Accumlate(std::vector<std::string> const& strings) noexcept
{
    auto ret = std::string{};

    for (auto i = 0U; i < strings.size(); ++i) {
        ret += strings[i];
    }

    return ret;
}

std::string Accumlate2(std::vector<std::string> const& strings) noexcept
{
    auto ret = std::string{};

#if 0  // old style
    for (std::vector<std::string>::const_iterator it = strings.cbegin(); it != strings.cend(); ++it) {
        ret += *it;
    }
#else
    for (auto it = strings.cbegin(); it != strings.cend(); ++it) {
        ret += *it;
    }
#endif

    return ret;
}

std::string Accumlate3(std::vector<std::string> const& strings) noexcept
{
    auto ret = std::string{};

    for (auto const& s : strings) {
        ret += s;
    }

    return ret;
}

TEST(ProgrammingConventionSyntaxA, RangeFor)
{
    ASSERT_EQ("abcd", Accumlate(std::vector<std::string>{"a", "b", "cd"}));
    ASSERT_EQ("ABCD", Accumlate2(std::vector<std::string>{"A", "B", "CD"}));
    ASSERT_EQ("AbCd", Accumlate3(std::vector<std::string>{"A", "b", "Cd"}));
}
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 下記のcopy_ifの第4引数をラムダ式を使って書き直せ。

TEST(ProgrammingConventionSyntaxA, Lambda)
{
    auto data = std::vector<std::string>{"", "abc", "", "d"};

    auto ret = std::vector<std::string>{};

    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(ret),
                 [](auto const& s) noexcept { return s.size() != 0; });
    ASSERT_EQ((std::vector<std::string>{"abc", "d"}), ret);
}
// @@@ sample end

// @@@ sample begin 2:0
// [A]
// 下記Lambda::GetNameLessThan()のラムダ式の問題点を修正し、単体テストを行え。
class Lambda {
public:
    explicit Lambda(std::vector<std::string>&& strs) : strs_{std::move(strs)} {}
    std::vector<std::string> GetNameLessThan(uint32_t length) const
    {
        auto ret = std::vector<std::string>{};

        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [length = length](auto const& str) noexcept { return (str.size() < length); });

        return ret;
    }

private:
    std::vector<std::string> strs_;
};

TEST(ProgrammingConventionSyntaxA, Lambda2)
{
    auto lambda = Lambda{{"abc", "abcdef", "a"}};

    ASSERT_EQ(lambda.GetNameLessThan(4), (std::vector<std::string>{"abc", "a"}));
    ASSERT_EQ(lambda.GetNameLessThan(2), (std::vector<std::string>{"a"}));
    ASSERT_EQ(lambda.GetNameLessThan(1), (std::vector<std::string>{}));
}
// @@@ sample end
}  // namespace
