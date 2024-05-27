#include <string>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
TEST(ProgrammingConventionTypeQ, GeneralInteger)
{
    // [Q]
    // 以下の組み込み型の使用方法は、その下のテストコードを(環境依存で)パスするが、
    // 適切であるとは言えない。適切な型に修正せよ。
    auto b = true;
    int  i{b};
    char c{-1};

    ASSERT_EQ(i * c, -1);
}
// @@@ sample end

// @@@ sample begin 1:0
double f(double a) noexcept { return 1 / a; }

TEST(ProgrammingConventionTypeQ, Float)
{
    // [Q]
    // 以下の両辺を同一と判定するための関数を作り、その関数の単体テストを行え。
    ASSERT_FALSE(1.0 == 1 + 0.001 - 0.001);

    // [Q]
    // 以下の0除算を捕捉するためのコードを書け。
    f(0.0);
}
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 以下のマクロ引数を型安全なenumに修正せよ

#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_BLUE 2

std::string GetString(int color)
{
    switch (color) {
    case COLOR_RED:
        return "Red";
    case COLOR_GREEN:
        return "Green";
    case COLOR_BLUE:
        return "Blue";
    default:
        assert(false);
        return "";
    }
}

TEST(ProgrammingConventionTypeQ, Enum)
{
    ASSERT_EQ(std::string{"Red"}, GetString(COLOR_RED));
    ASSERT_EQ(std::string{"Green"}, GetString(COLOR_GREEN));
    ASSERT_EQ(std::string{"Blue"}, GetString(COLOR_BLUE));
}
// @@@ sample end

// @@@ sample begin 3:0
int32_t array_value() noexcept
{
    static int32_t i;

    return i++;
}

TEST(ProgrammingConventionTypeQ, Array)
{
    // [Q]
    // 以下の配列の値の設定を範囲for文を使って書き直せ
    int32_t array[10];

    for (auto i = 0U; i < sizeof(array) / sizeof(array[0]); ++i) {
        array[i] = array_value();
    }

    ASSERT_EQ(0, array[0]);
    ASSERT_EQ(3, array[3]);
    ASSERT_EQ(9, array[9]);
}
// @@@ sample end

// @@@ sample begin 4:0
// [Q]
// 以下のtypedefをC++11から導入された新しい形式のエイリアスに直せ。
typedef unsigned char uchar;
typedef bool (*func_type)(int32_t);

// [Q]
// template引数で与えられた型のオブジェクトをstd::vectorで保持するエイリアスtemplateを
// 定義し、その単体テストを行え。

// @@@ sample end

// @@@ sample begin 5:0
// [Q]
// 下記のStringHolderに「const/constexprを付加する」等を行い、より良いコードに修正せよ。

class StringHolder {
public:
    StringHolder() = default;
    void Add(std::string str)
    {
        if (vector_len_max_ > strings_.size()) {
            strings_.push_back(str);
        }
    }

    std::vector<std::string> GetStrings() const { return strings_; }

private:
    size_t                   vector_len_max_{3};
    std::vector<std::string> strings_{};
};

TEST(ProgrammingConventionTypeQ, ConstConstexpr)
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
// [Q]
// 下記の"DISABLED_"を削除し、何が起こるのか、なぜそうなるのかを確かめた上で、
// nameの型やその初期化を行っているコードを修正せよ。
TEST(DISABLED_ProgrammingConventionQ, ConstConstexpr2)
{
    char* name = const_cast<char*>("abcdef");

    for (auto i = 0U; name[i] != '\0'; ++i) {
        name[i] = std::toupper(name[i]);
    }

    ASSERT_STREQ("ABCDEF", name);
    ASSERT_EQ("ABCDEF", std::string{name});
}
// @@@ sample end

// @@@ sample begin 7:0
int32_t literal_test(int64_t) noexcept { return 0; }
int32_t literal_test(int32_t*) noexcept { return 1; }

// [Q]
// 下記変数の初期化コードをコメントに基づき適切に修正せよ。
TEST(ProgrammingConventionTypeQ, Literal)
{
    int32_t* p{NULL};                // NULLは使用不可
    uint64_t a{0x1234567890abcdef};  // 適切なセパレータを挿入
    int32_t  b{0x715};               // ビット表現に修正

    // [Q]
    // 下記resultはfalseになるが、その理由を述べ、trueになるようにコードを修正せよ。
    bool const result{(literal_test(NULL) == literal_test(p))};
    ASSERT_FALSE(result);

    ASSERT_EQ(0x1234567890abcdef, a);
    ASSERT_EQ(b, 0x715);
}
// @@@ sample end

// @@@ sample begin 8:0
TEST(ProgrammingConventionTypeQ, Initialization)
{
    // [Q]
    // 変数a、b、v、wの定義と初期化を1文で行え。
    {
        int32_t a[3];

        for (auto& r : a) {
            r = 1;
        }

        ASSERT_EQ(1, a[0]);
        ASSERT_EQ(1, a[1]);
        ASSERT_EQ(1, a[2]);
    }
    {
        int32_t b[3];

        for (auto& r : b) {
            r = 0;
        }

        ASSERT_EQ(0, b[0]);
        ASSERT_EQ(0, b[1]);
        ASSERT_EQ(0, b[2]);
    }
    {
        auto v = std::vector<std::string>{3};

        for (auto& r : v) {
            r = "1";
        }

        ASSERT_EQ("1", v[0]);
        ASSERT_EQ("1", v[1]);
        ASSERT_EQ("1", v[2]);
    }
    {
        auto w = std::vector<std::string>{};

        for (auto i = 0; i < 3; ++i) {
            w.emplace_back(std::to_string(i));
        }

        ASSERT_EQ("0", w[0]);
        ASSERT_EQ("1", w[1]);
        ASSERT_EQ("2", w[2]);
    }
}
// @@@ sample end

}  // namespace
