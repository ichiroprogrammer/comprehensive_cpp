#include <cfenv>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace {

// @@@ sample begin 0:0
TEST(ProgrammingConventionTypeA, GeneralInteger)
{
    // [A]
    // 以下の組み込み型の使用方法は、その下のテストコードを(環境依存で)パスするが、
    // 適切であるとは言えない。適切な型に修正せよ。
    int32_t b{1};
    int32_t i{b};
    int32_t c{-1};

    ASSERT_EQ(i * c, -1);
}
// @@@ sample end

// @@@ sample begin 1:0
double f(double a) noexcept { return 1 / a; }

template <typename FLOAT_0, typename FLOAT_1>
bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs)
{
    static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
    static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

    return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
}

TEST(ProgrammingConventionTypeA, Float)
{
    // [A]
    // 以下の両辺を同一と判定するための関数を作り、その関数の単体テストを行え。
    ASSERT_TRUE(is_equal(1.0, 1 + 0.001 - 0.001));

    // [A]
    // 以下の0除算を捕捉するためのコードを書け。
    std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア
    f(0.0);
    ASSERT_TRUE(std::fetestexcept(FE_ALL_EXCEPT) & FE_DIVBYZERO);
    std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア
}
// @@@ sample end

// @@@ sample begin 2:0
// [A]
// 以下のマクロ引数を型安全なenumに修正せよ

enum class Color { Red, Green, Blue };

std::string GetString(Color color)
{
    switch (color) {
    case Color::Red:
        return "Red";
    case Color::Green:
        return "Green";
    case Color::Blue:
        return "Blue";
    default:
        assert(false);
        return "";
    }
}

TEST(ProgrammingConventionTypeA, Enum)
{
    ASSERT_EQ(std::string{"Red"}, GetString(Color::Red));
    ASSERT_EQ(std::string{"Green"}, GetString(Color::Green));
    ASSERT_EQ(std::string{"Blue"}, GetString(Color::Blue));
}
// @@@ sample end

// @@@ sample begin 3:0
int32_t array_value() noexcept
{
    static int32_t i;

    return i++;
}

TEST(ProgrammingConventionTypeA, Array)
{
    // [A]
    // 以下の配列の値の設定を範囲for文を使って書き直せ
    int32_t array[10];

    for (auto& a : array) {
        a = array_value();
    }

    ASSERT_EQ(0, array[0]);
    ASSERT_EQ(3, array[3]);
    ASSERT_EQ(9, array[9]);
}
// @@@ sample end

// @@@ sample begin 4:0
// [A]
// 以下のtypedefをC++11から導入された新しい形式のエイリアスに直せ。
using uchar     = unsigned char;
using func_type = bool (*)(int32_t);

// [A]
// template引数で与えられた型のオブジェクトをstd::vectorで保持するエイリアスtemplateを
// 定義し、その単体テストを行え。
template <class T>
using TypeVector = std::vector<T>;

TEST(ProgrammingConventionTypeA, Alias)
{
    auto a = TypeVector<std::string>{"abc", "de", "f"};

    ASSERT_EQ((std::vector<std::string>{"abc", "de", "f"}), a);
    ASSERT_EQ(3, a.size());
}
// @@@ sample end

// @@@ sample begin 5:0
// [A]
// 下記のStringHolderに「const/constexprを付加する」等を行い、より良いコードに修正せよ。

class StringHolder {
public:
    StringHolder() = default;
    void Add(std::string const& str)
    {
        if (vector_len_max_ > strings_.size()) {
            strings_.push_back(str);
        }
    }

    std::vector<std::string> const& GetStrings() const noexcept { return strings_; }

private:
    static constexpr size_t  vector_len_max_{3};
    std::vector<std::string> strings_{};
};

TEST(ProgrammingConventionTypeA, ConstConstexpr)
{
    auto sh = StringHolder{};

    ASSERT_EQ(std::vector<std::string>{}, sh.GetStrings());

    sh.Add("a");
    sh.Add(std::string{"bc"});
    ASSERT_EQ((std::vector<std::string>{"a", "bc"}), sh.GetStrings());

    sh.Add("def");
    sh.Add(std::string{"g"});
    ASSERT_EQ((std::vector<std::string>{"a", "bc", "def"}), sh.GetStrings());
}
// @@@ sample end

// @@@ sample begin 6:0
// [A]
// 下記の"DISABLED_"を削除し、何が起こるのか、なぜそうなるのかを確かめた上で、
// nameの型やその初期化を行っているコードを修正せよ。
TEST(ProgrammingConventionTypeA, ConstConstexpr2)
{
    char name[] = "abcdef";

    for (auto& n : name) {
        n = std::toupper(n);
    }

    ASSERT_STREQ("ABCDEF", name);
    ASSERT_EQ("ABCDEF", std::string{name});
}
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_FUNC;

// @@@ sample begin 7:0
int32_t literal_test(int64_t) noexcept { return 0; }
int32_t literal_test(int32_t*) noexcept { return 1; }

// [A]
// 下記変数の初期化コードをコメントに基づき適切に修正せよ。
TEST(ProgrammingConventionTypeA, Literal)
{
    int32_t* p{nullptr};                // NULLは使用不可
    uint64_t a{0x1234'5678'90ab'cdef};  // 適切なセパレータを挿入
    int32_t  b{0b0111'0001'0101};       // ビット表現に修正

    // [A]
    // 下記resultはfalseになるが、その理由を述べ、trueになるようにコードを修正せよ。
    bool const result{(literal_test(nullptr) == literal_test(p))};
    ASSERT_TRUE(result);

    ASSERT_EQ(0x1234567890abcdef, a);
    ASSERT_EQ(b, 0x715);
}
// @@@ sample end
SUPPRESS_WARN_END;

// @@@ sample begin 8:0
TEST(ProgrammingConventionTypeA, Initialization)
{
    // [A]
    // 変数a、b、v、wの定義と初期化を1文で行え。
    {
        int32_t a[3]{1, 1, 1};

        ASSERT_EQ(1, a[0]);
        ASSERT_EQ(1, a[1]);
        ASSERT_EQ(1, a[2]);
    }
    {
        int32_t b[3]{};

        ASSERT_EQ(0, b[0]);
        ASSERT_EQ(0, b[1]);
        ASSERT_EQ(0, b[2]);
    }
    {
        auto v = std::vector<std::string>{3, std::string{"1"}};

        ASSERT_EQ("1", v[0]);
        ASSERT_EQ("1", v[1]);
        ASSERT_EQ("1", v[2]);
    }
    {
        auto w = std::vector<std::string>{"0", "1", "2"};

        ASSERT_EQ("0", w[0]);
        ASSERT_EQ("1", w[1]);
        ASSERT_EQ("2", w[2]);
    }
}
// @@@ sample end

}  // namespace
