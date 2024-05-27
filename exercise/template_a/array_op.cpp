#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// 配列を引数に取り、その長さを返す関数テンプレートarray_lengthを作れ。

template <typename T, size_t N>
constexpr size_t array_length(T const (&)[N]) noexcept
{
    return N;
}

namespace {

TEST(TemplateMetaProgrammingA, array_length)
{
    int         i[5];
    std::string str[]{"a", "b", "c"};

    static_assert(array_length(i) == 5);
    static_assert(array_length(str) == 3);
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 配列を引数に取り、その次元を返す関数テンプレートarray_dimensionを作れ。

constexpr size_t array_dimension(...) noexcept { return 0; }

template <typename T, size_t N>
constexpr size_t array_dimension(T const (&t)[N]) noexcept
{
    return 1 + array_dimension(t[0]);
}

namespace {

TEST(TemplateMetaProgrammingA, array_dimension)
{
    constexpr int i1[5]{};
    constexpr int i2[5][2]{};
    constexpr int i3[5][2][3]{};

    static_assert(array_dimension(i1) == 1);
    static_assert(array_dimension(i2) == 2);
    static_assert(array_dimension(i3) == 3);
}
}  // namespace
// @@@ sample end
