#include <algorithm>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace {
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_DEPRECATED;
// @@@ sample begin 0:0
// [Q]
// 下記Accumlateのfor文を
//  * イテレータを使ったfor文を使用したAccumlate2
//  * 範囲for文を使用したAccumlate3
// を作り、それらの単体テストを行え。また、その時にその他の不具合があれば合わせて修正せよ。
std::string Accumlate(std::vector<std::string> strings) noexcept
{
    auto ret = std::string{};

    for (auto i = 0U; i < strings.size(); ++i) {
        ret += strings[i];
    }

    return ret;
}

TEST(ProgrammingConventionSyntaxQ, RangeFor)
{
    ASSERT_EQ("abcd", Accumlate(std::vector<std::string>{"a", "b", "cd"}));
}
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 下記のcopy_ifの第4引数をラムダ式を使って書き直せ。
bool is_not_size0(std::string const& s) noexcept { return s.size() != 0; }

TEST(ProgrammingConventionSyntaxQ, Lambda)
{
    auto data = std::vector<std::string>{"", "abc", "", "d"};

    auto ret = std::vector<std::string>{};

    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(ret), is_not_size0);
    ASSERT_EQ((std::vector<std::string>{"abc", "d"}), ret);
}
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 下記Lambda::GetNameLessThan()のラムダ式の問題点を修正し、単体テストを行え。
class Lambda {
public:
    explicit Lambda(std::vector<std::string>&& strs) : strs_{std::move(strs)} {}
    std::vector<std::string> GetNameLessThan(uint32_t length) const
    {
        auto ret = std::vector<std::string>{};

        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [=](auto const& str) noexcept { return (strs_.size() < length); });

        return ret;
    }

private:
    std::vector<std::string> strs_;
};

TEST(ProgrammingConventionSyntaxQ, Lambda2)
{
    auto lambda = Lambda{{"abc", "abcdef", "a"}};

    // 以下に単体テストを追加。
}
// @@@ sample end
SUPPRESS_WARN_END;
}  // namespace
