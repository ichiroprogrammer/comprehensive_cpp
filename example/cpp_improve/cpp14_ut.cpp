#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0

auto add(int a, int b)
{                  // C++14 通常関数の戻り値型推論
    return a + b;  // return文から戻り値の型を推論(int型)
}
// @@@ sample end

TEST(cpp14, normal_func_retun_deduction)
{
    // @@@ sample begin 0:1

    ASSERT_EQ(3, add(1, 2));
    // @@@ sample end
}

// @@@ sample begin 1:0

static int static_value = 3;

auto func0() -> auto& { return static_value; }
auto func1() -> auto { return static_value; }

auto func2 = []() -> auto& { return static_value; };
auto func3 = []() -> auto { return static_value; };
// @@@ sample end

TEST(cpp14, normal_func_retun_deduction2)
{
    // @@@ sample begin 1:1

    ASSERT_EQ(3, func0());
    ASSERT_EQ(3, func1());
    decltype(auto) ret0 = func0();  // static_valueの参照を返す
    ret0                = 4;
    ASSERT_EQ(4, func0());
    ASSERT_EQ(4, func3());

    decltype(auto) ret2 = func2();  // static_valueの参照を返す
    ret2                = 3;
    ASSERT_EQ(3, func2());
    ASSERT_EQ(3, func3());
    // @@@ sample end
}

// @@@ sample begin 2:0

template <typename T>
constexpr T pi = T{3.1415926535897932385};  // C++14 変数テンプレートの例

// @@@ sample end

TEST(cpp14, template_val)
{
    // @@@ sample begin 2:1

    static_assert(
        std::is_same_v<const double, decltype(pi<double>)>);  // is_same_vも定数テンプレート
    // @@@ sample end
}

}  // namespace
