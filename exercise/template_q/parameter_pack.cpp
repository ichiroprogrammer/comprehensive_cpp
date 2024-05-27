#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記の関数Maxは、単体テストが示す通り、2つのパラメータの大きい方を返す。
// 任意の個数の引数を取れるようにMaxを修正せよ。

template <typename T>
T Max(T const& t0, T const& t1) noexcept
{
    return t0 > t1 ? t0 : t1;
}

TEST(TemplateMetaProgrammingQ, parameter_pack)
{
    ASSERT_EQ(2, Max(1, 2));
    ASSERT_EQ("bcd", Max(std::string{"abc"}, std::string{"bcd"}));
}
// @@@ sample end
}  // namespace
