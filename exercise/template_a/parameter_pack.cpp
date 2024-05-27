#include <utility>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記の関数Maxは、単体テストが示す通り、2つのパラメータの大きい方を返す。
// 任意の個数の引数を取れるようにMaxを修正せよ。

// 解答例1
// パラメータパックを使用しMaxを修正した例
template <typename T>
T Max(T const& t0, T const& t1) noexcept
{
    return t0 > t1 ? t0 : t1;
}

template <typename HEAD, typename... ARGS>
auto Max(HEAD const& head, ARGS const&... args) noexcept
{
    auto args_max = Max(args...);

    return head > args_max ? head : args_max;
}

TEST(TemplateMetaProgrammingA, parameter_pack)
{
    ASSERT_EQ(2, Max(1, 2));
    ASSERT_EQ("bcd", Max(std::string{"abc"}, std::string{"bcd"}));

    ASSERT_EQ(3, Max(1, 2, 3));
    ASSERT_EQ("efg", Max(std::string{"abc"}, std::string{"bcd"}, std::string{"efg"}));
}

// 解答例2
// std::initializer_listを使用しMaxを修正した例
template <typename T>
T Max(std::initializer_list<T> t_list) noexcept
{
    auto ret   = T{};
    auto first = true;

    for (auto const& t : t_list) {
        if (std::exchange(first, false)) {
            ret = t;
        }
        else {
            ret = Max(ret, t);
        }
    }

    return ret;
}

TEST(TemplateMetaProgrammingA, initializer_list)
{
    ASSERT_EQ(2, Max({1, 2}));
    ASSERT_EQ("bcd", Max({std::string{"abc"}, std::string{"bcd"}}));

    ASSERT_EQ(3, Max({1, 2, 3}));
    ASSERT_EQ("efg", Max({std::string{"abc"}, std::string{"bcd"}, std::string{"efg"}}));
}
// @@@ sample end
}  // namespace
