#include <tuple>
#include <type_traits>
#include <variant>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0

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
    // @@@ sample begin 0:1

    auto a = A{1, 2};

    auto [a0, a1] = f(a);  // fはA::a0_、a1_にアクセスできる

    ASSERT_EQ(a0, 1);
    ASSERT_EQ(a1, 2);
    // @@@ sample end
}
}  // namespace

// @@@ sample begin 1:0

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
    // @@@ sample begin 1:1

    // C++17までのスタイル
    Point2D p2d{10, 20};

    auto [x2d, y2d] = p2d;
    ASSERT_EQ(x2d, 10);
    ASSERT_EQ(y2d, 20);

    // C++20から
    Point3D p3d{1, 2, 3};

    auto [p3d_x, p3d_y, p3d_z] = p3d;
    ASSERT_EQ(p3d_x, 1);
    ASSERT_EQ(p3d_y, 2);
    ASSERT_EQ(p3d_z, 3);
    // @@@ sample end
}

#if defined(__clang_analizer__)
// @@@ sample begin 2:0

template <typename T>

struct Ommit {
    using value_type = T::value_type;  // C++20では typename を省略できる

    value_type get_first_element(const T& container) const { return container[0]; }
};
// @@@ sample end

TEST(cpp20, template_ommit_typename)
{
    std::vector<int> vec{1, 2, 3};

    Ommit<std::vector<int>> ex;
    int                     first_element = ex.get_first_element(vec);

    ASSERT_EQ(1, first_element);
}

// @@@ sample begin 3:0

struct X1 {
    int   i;
    float f;

    friend bool operator==(const X1&, const X1&) = default;
};

struct X2 {
    int   i;
    float f;

    constexpr X2(int i, float f) : i{i}, f{f} {}

    friend bool operator==(const X2&, const X2&) = default;
};

template <int N>
struct C1 {
    static constexpr int value = N;
};

template <float N>
struct C2 {
    static constexpr float value = N;  // N を保持
};

template <X1 x1, X2 x2>
struct C3 {
    static constexpr X1 value1 = x1;  // X1 の値を保持
    static constexpr X2 value2 = x2;  // X2 の値を保持
};

template <auto V>
struct C4 {
    static constexpr decltype(V) value = V;  // V の型を推論し、その値を保持
};
// @@@ sample end
// @@@ sample begin 3:1

static_assert(C1<42>::value == 42);  // テンプレートパラメータ N = 42 の動作を確認

static_assert(C2<3.14f>::value == 3.14f);  // テンプレートパラメータ N = 3.14f の動作を確認

constexpr X1 x1{1, 2.5f};  // X1 のオブジェクトを constexpr で作成
constexpr X2 x2{2, 3.5f};  // X2 のオブジェクトを constexpr で作成

static_assert(C3<x1, x2>::value1 == x1);  // X1 の比較
static_assert(C3<x1, x2>::value2 == x2);  // X2 の比較

static_assert(C4<100>::value == 100);  // 整数の動作確認
static_assert(C4<x1>::value == x1);    // X1 オブジェクトの動作確認
// @@@ sample end
}  // namespace

// @@@ sample begin 4:0
namespace adl_NS {
struct X {};

// X に対する関数テンプレート
template <typename T>
void func(T)
{
    std::cout << "Called func(T) from my_namespace" << std::endl;
}
}  // namespace adl_NS
// @@@ sample end

TEST(cpp20, template_union_struct)
{
    // @@@ sample begin 4:1

    adl_NS::X obj;

    // 型を明示的に指定して呼び出す（C++20以前では ADL が効かない）
    func<adl_NS::X>(obj);  // エラー: ADL が働かず、関数が見つからない

    // 型を明示的に指定せずに呼び出す（ADLが働く）
    func(obj);  // OK: adl_NS から func が見つかる
    // @@@ sample end
}

namespace {
// @@@ sample begin 5:0

template <typename T>
class X {
public:
    X(T value) : value_{value} {}
    T getValue() const { return value_; }

private:
    T value_;
};
template <typename T>
using XAlias = X<T>;
// @@@ sample end

TEST(cpp20, template_alias)
{
    // @@@ sample begin 5:1

    XAlias obj1{42};  // 推論される型はint
    static_assert(std::is_same_v<decltype(obj1), X<int>>);

    XAlias obj2{3.14};  // 推論される型はdouble
    static_assert(std::is_same_v<decltype(obj2), X<double>>);

    EXPECT_EQ(obj1.getValue(), 42);
    EXPECT_DOUBLE_EQ(obj2.getValue(), 3.14);
    // @@@ sample end
}
// @@@ sample begin 6:0

template <class T>
struct Point {
    T x;
    T y;
};
// @@@ sample end

TEST(cpp20, template_union_struct)
{
    // @@@ sample begin 6:1

    Point p{3.0, 4.0};  // C++17:NG C++20:OK

    ASSERT_DOUBLE_EQ(p.x, 3.0);
    ASSERT_DOUBLE_EQ(p.y, 4.0);
    // @@@ sample end
}
#endif
}  // namespace
