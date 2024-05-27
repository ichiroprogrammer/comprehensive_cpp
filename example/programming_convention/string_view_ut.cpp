#include <string>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace {

TEST(ProgrammingConvention, string_view)
{
    // @@@ sample begin 0:0

    auto str = std::string{"abc"};
    auto sv  = std::string_view{str};  // OK lvalueからの初期化

    ASSERT_EQ(sv, std::string_view{"abc"});
    // @@@ sample end
}

#define SANITIZER_NG 1

#if SANITIZER_NG == 1
#define string_view_san_ng_Opt DISABLED_string_view_san_ng
#else
#define string_view_san_ng_Opt string_view_san_ng
#endif
TEST(ProgrammingConvention, string_view_san_ng_Opt)
{
    SUPPRESS_WARN_BEGIN;
    SUPPRESS_WARN_CLANG_DANGLING_GSL;
    // @@@ sample begin 0:1

    std::string_view sv = std::string{"abc"};  // NG rvalueからの初期化
                                               //    この行でstd::string{"abc"}が解放
    ASSERT_EQ(sv, std::string_view{"abc"});    //    svは無効なポインタを保持
    // @@@ sample end

    SUPPRESS_WARN_END;
}

TEST(ProgrammingConvention, string_view_no_null_terminate)
{
    // @@@ sample begin 1:0

    {  // 文字列リテラルを範囲として使用すると、ヌル文字が要素に含まれる
        auto oss = std::ostringstream{};

        for (char c : "abc") {
            oss << c;
        }

        ASSERT_EQ((std::string{'a', 'b', 'c', '\0'}), oss.str());  // ヌル文字が入る
    }
    {  // string_viewを使用すると、ヌル文字が要素に含まれない
        auto oss = std::ostringstream{};

        for (char c : std::string_view{"abc"}) {
            oss << c;
        }

        ASSERT_EQ((std::string{'a', 'b', 'c'}), oss.str());  // ヌル文字は入らない
    }
    // @@@ sample end
    {
        // @@@ sample begin 2:0

        char const a[]{"123"};
        auto       b = std::string_view{"01234"}.substr(1, 3);  // インデックス1 - 3

        ASSERT_EQ(a, b);  // a == bが成り立つ

        auto oss_a = std::ostringstream{};
        oss_a << a;

        auto oss_b = std::ostringstream{};
        oss_b << b;

        ASSERT_EQ(oss_a.str(), oss_b.str());  // ここまでは予想通り

        // clang-format off
        // bをインデックスアクセスすると以下のようになる。
        ASSERT_EQ('0', b[-1]); ASSERT_EQ('1', b[0]); ASSERT_EQ('2',  b[1]);
        ASSERT_EQ('3',  b[2]); ASSERT_EQ('4', b[3]); ASSERT_EQ('\0', b[4]);
        // clang-format on

        // 上記の結果から、以下の結果になることには注意が必要
        auto oss_b_cstr = std::ostringstream{};
        oss_b_cstr << b.data();  // data()は文字列リテラルへのポインタを指す。

        ASSERT_NE(oss_a.str(), oss_b_cstr.str());
        ASSERT_EQ("123", oss_a.str());
        ASSERT_EQ("1234", oss_b_cstr.str());
        // @@@ sample end
    }
}
}  // namespace
