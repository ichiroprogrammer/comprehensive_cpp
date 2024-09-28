#include <tuple>
#include <type_traits>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0

template <typename T>
class Box {
public:
    // clang-format off
    template <typename U>
    explicit(std::is_integral_v<U>) Box(U value) : value_(static_cast<T>(value)) { }
    //       ^^^^Uがintegerの場合のみexplicit

    T getValue() const { return value_; }

private:
    T value_;
    // clang-format on
};
// @@@ sample end

// テストケース
TEST(cpp20, box_construction)
{
    // @@@ sample begin 0:1

    Box<int> intBox{42};  // 明示的な構築
    EXPECT_EQ(intBox.getValue(), 42);

    // 以下はコンパイルエラー
    // Box<int> implicitIntBox = 42;  // コンストラクタがexplicit(false)であるた

    // static_assertを使用して、コンパイル時にexplicitであることを確認
    static_assert(std::is_constructible_v<Box<int>, int>);
    static_assert(!std::is_convertible_v<int, Box<int>>);

    //
    Box<float> floatBox{3.14f};  // 明示的な構築
    EXPECT_FLOAT_EQ(floatBox.getValue(), 3.14f);

    Box<float> implicitFloatBox = 2.71f;  // explicit(true)であるため、暗黙の変換が許可される
    EXPECT_FLOAT_EQ(implicitFloatBox.getValue(), 2.71f);

    // static_assertを使用して、コンパイル時に非explicitであることを確認
    static_assert(std::is_constructible_v<Box<float>, float>);
    static_assert(std::is_convertible_v<float, Box<float>>);
    // @@@ sample end
}

// @@@ sample begin 1:0

class A {
public:
    A(int a0, int b0) : a0_{a0}, b0_{b0} {}

private:
    int a0_;
    int b0_;

    friend std::pair<int, int> f(A const& a)
    {
        auto [a_a, a_b] = a;  // fがfriendであるため、構造化束縛可能

        return {a_a, a_b};
    }
};
// @@@ sample end

TEST(cpp20, structed_bind)
{
    // @@@ sample begin 1:1

    auto a = A{1, 2};

    auto [a0, a1] = f(a);  // fはA::a0_、a1_にアクセスできる

    ASSERT_EQ(a0, 1);
    ASSERT_EQ(a1, 2);
    // @@@ sample end
}
}  // namespace

// @@@ sample begin 2:0

struct Point2D {  // C++17でも動作する例
    int x, y;
};

class Point3D {  // C++20で改善された例
public:
    Point3D(int x, int y, int z) : x_{x}, y_{y}, z_{z} {}

    template <std::size_t I>  // 構造化束縛カスタマイゼーションポイント
    auto get() const
    {
        if constexpr (I == 0)
            return x_;
        else if constexpr (I == 1)
            return y_;
        else if constexpr (I == 2)
            return z_;
    }

private:
    int x_, y_, z_;
};

namespace std {  // 例外的にstdへの追加が認められている
template <>      // 構造化束縛のためのカスタマイゼーションポイント
struct tuple_size<Point3D> : std::integral_constant<std::size_t, 3> {
};

template <std::size_t I>
struct tuple_element<I, Point3D> {
    using type = int;
};
}  // namespace std
// @@@ sample end

namespace {
TEST(cpp20, structed_bind_specitalize)
{
    // @@@ sample begin 2:1

    // C++17まで動作
    Point2D p2d{10, 20};

    auto [x2d, y2d] = p2d;
    EXPECT_EQ(x2d, 10);
    EXPECT_EQ(y2d, 20);

    // C++20から
    Point3D p3d{1, 2, 3};

    auto [p3d_x, p3d_y, p3d_z] = p3d;
    EXPECT_EQ(p3d_x, 1);
    EXPECT_EQ(p3d_y, 2);
    EXPECT_EQ(p3d_z, 3);
    // @@@ sample end
}
}  // namespace
