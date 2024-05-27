#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// 配列を引数に取り、その長さを返す関数テンプレートarray_lengthを作れ。

namespace {

TEST(TemplateMetaProgrammingQ, array_length)
{
#if 0
    int         i[5];
    std::string str[]{"a", "b", "c"};

    static_assert(array_length(i) == 5);
    static_assert(array_length(str) == 3);
#endif
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 配列を引数に取り、その次元を返す関数テンプレートarray_dimensionを作れ。

namespace {

TEST(TemplateMetaProgrammingQ, array_dimension)
{
#if 0
    constexpr int i1[5]{};
    constexpr int i2[5][2]{};
    constexpr int i3[5][2][3]{};

    static_assert(array_dimension(i1) == 1);
    static_assert(array_dimension(i2) == 2);
    static_assert(array_dimension(i3) == 3);
#endif
}
}  // namespace
// @@@ sample end
