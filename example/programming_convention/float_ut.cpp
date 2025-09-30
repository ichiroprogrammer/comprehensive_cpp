#include <cfenv>
#include <cmath>
#include <limits>

#include "gtest_wrapper.h"

namespace {

TEST(ProgrammingConvention, float_comp_0)
{
    // @@@ sample begin 0:0

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    //  ASSERT_EQ(0.05F, a + b);  // NG  a + b == 0.05Fは一般には成立しない。
    ASSERT_NE(0.05F, a + b);
    // @@@ sample end
}

// @@@ sample begin 0:1

/// @brief float比較用関数
bool is_equal_f(float lhs, float rhs) noexcept { return std::abs(lhs - rhs) <= std::numeric_limits<float>::epsilon(); }
// @@@ sample end

TEST(ProgrammingConvention, float_comp_1)
{
    // @@@ sample begin 0:2

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // floatの比較はis_equal_fのような関数を使う。
    ASSERT_TRUE(is_equal_f(0.05F, a + b));  // OK
    // @@@ sample end
}
// @@@ sample end

// @@@ sample begin 0:3

// 上記例と似たソースコードであるが、下記のような問題が起こる
/// @brief double比較用関数
bool is_equal_d(double lhs, double rhs) noexcept
{
    return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon();
}
// @@@ sample end

TEST(ProgrammingConvention, float_comp_2)
{
    // @@@ sample begin 0:4

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatの精度のまま、is_equal_dの引数の型であるdoubleに昇格される。
    // 一方、0.05はdoubleであるため(循環小数をdoubleの精度で切り捨てた値であるため)、
    // a + b(floatの精度の値)と0.05の差はdoubleのepsilonを超える。
    //  ASSERT_TRUE(is_equal_d(0.05, a + b));  // NG
    ASSERT_FALSE(is_equal_d(0.05, a + b));
    // @@@ sample end
}

// @@@ sample begin 0:5

// is_equal_dを改良して、引数の型が統一されていない呼び出しをコンパイルエラーにできるようにした。
/// @brief 浮動小数点比較用関数
template <typename FLOAT_0, typename FLOAT_1>
bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
{
    static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
    static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

    return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
}
// @@@ sample end

TEST(ProgrammingConvention, float_comp_3)
{
    // @@@ sample begin 0:6

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatであり、0.05はdoubleであるため、下記コードはコンパイルできない。
    // ASSERT_TRUE(is_equal(0.05, a + b));
    ASSERT_TRUE(is_equal(0.05F, a + b));  // OK リテラルに型を指定して、引数の型を統一
    // @@@ sample end
}
}  // namespace
