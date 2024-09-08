#include <chrono>
#include <complex>
#include <sstream>
#include <tuple>
#include <utility>

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

// @@@ sample begin 3:0

template <typename Tuple, std::size_t... I>
std::string tuple2string(const Tuple& t, std::index_sequence<I...>)
{
    std::ostringstream os;

    ((os << std::get<I>(t) << " "), ...);  // Tupleの各要素を出力

    return os.str();
}

template <typename... Args>
std::string process_tuple(const std::tuple<Args...>& t)
{
    return tuple2string(t, std::index_sequence_for<Args...>{});
}
// @@@ sample end

TEST(cpp14, integer_sequence)
{
    // @@@ sample begin 3:1

    std::tuple<int, double, const char*> t(1, 2.5, "test");

    auto ret = process_tuple(t);  // タプルの要素を出力 (1, 2.5, test)
    ASSERT_EQ("1 2.5 test ", ret);
    ASSERT_EQ(1, std::get<0>(t));
    ASSERT_EQ(2.5, std::get<1>(t));
    ASSERT_STREQ("test", std::get<2>(t));
    // @@@ sample end
}

TEST(cpp14, tupple_get)
{
    // @@@ sample begin 4:0

    std::tuple<int, float, std::string> my_tuple(1, 3.14f, "hello");

    // 異なる型のオーバーロードされた std::get を使用
    ASSERT_EQ(std::get<int>(my_tuple), 1);
    ASSERT_FLOAT_EQ(std::get<float>(my_tuple), 3.14f);
    ASSERT_EQ(std::get<std::string>(my_tuple), "hello");
    // @@@ sample end
}

TEST(cpp14, s_literal)
{
    // @@@ sample begin 5:0

    using namespace std::string_literals;  // "s" リテラルを使用

    std::string str = "Hello"s + ", World!";

    ASSERT_EQ(str, "Hello, World!");
    // @@@ sample end
}

TEST(cpp14, chrono_literal)
{
    // @@@ sample begin 6:0

    using namespace std::chrono_literals;

    auto ten_seconds  = 10s;
    auto five_minutes = 5min;
    auto half_hour    = 0.5h;

    ASSERT_EQ(ten_seconds.count(), 10);
    ASSERT_EQ(five_minutes.count(), 5);
    ASSERT_DOUBLE_EQ(half_hour.count(), 0.5);
    // @@@ sample end
}

TEST(cpp14, complex_literal)
{
    // @@@ sample begin 7:0

    using namespace std::complex_literals;

    std::complex<double> c1 = 1.0 + 2i;
    std::complex<double> c2 = 2.0 - 3i;

    ASSERT_DOUBLE_EQ(c1.real(), 1.0);
    ASSERT_DOUBLE_EQ(c1.imag(), 2.0);
    ASSERT_DOUBLE_EQ(c2.real(), 2.0);
    ASSERT_DOUBLE_EQ(c2.imag(), -3.0);
    // @@@ sample end
}
}  // namespace
