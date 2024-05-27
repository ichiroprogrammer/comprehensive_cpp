#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記関数ColorMask2Strはuint32_t型のビットマスクを引数に取る。
// これはユーザが使用間違いを起こしやすい脆弱なインターフェースである。
// enumによるビットマスク表現を使用しこの問題に対処せよ。

enum class Color : uint32_t {
    RED    = 0b0001,
    YELLOW = 0b0010,
    GREEN  = 0b0100,
    BLUE   = 0b1000,
};

constexpr Color operator&(Color x, Color y) noexcept
{
    return static_cast<Color>(static_cast<uint32_t>(x) & static_cast<uint32_t>(y));
}

constexpr Color operator|(Color x, Color y) noexcept
{
    return static_cast<Color>(static_cast<uint32_t>(x) | static_cast<uint32_t>(y));
}

Color& operator&=(Color& x, Color y) noexcept { return x = x & y; }
Color& operator|=(Color& x, Color y) noexcept { return x = x | y; }

constexpr bool IsTrue(Color x) noexcept { return static_cast<bool>(x); }

std::string ColorMask2Str(Color color)
{
    auto ret = std::string{};

    if (IsTrue(Color::RED & color)) {
        ret += "RED";
    }
    if (IsTrue(Color::YELLOW & color)) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "YELLOW";
    }
    if (IsTrue(Color::GREEN & color)) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "GREEN";
    }
    if (IsTrue(Color::BLUE & color)) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "BLUE";
    }

    return ret;
}

TEST(DesignPatternA, EnumBitmask)
{
    ASSERT_EQ("RED", ColorMask2Str(Color::RED));
    ASSERT_EQ("RED,YELLOW", ColorMask2Str(Color::RED | Color::YELLOW));
    ASSERT_EQ("YELLOW", ColorMask2Str(Color::YELLOW));
    ASSERT_EQ("YELLOW,GREEN,BLUE", ColorMask2Str(Color::YELLOW | Color::GREEN | Color::BLUE));

    auto c = Color::GREEN;
    ASSERT_EQ("GREEN", ColorMask2Str(c));

    c |= Color::RED;
    ASSERT_EQ("RED,GREEN", ColorMask2Str(c));

    c &= Color::RED;
    ASSERT_EQ("RED", ColorMask2Str(c));

#if 0  // 間違った使い方はコンパイルさせない
    ASSERT_EQ("", ColorMask2Str(0b10000)); // 想定していない使用法
#endif
}
// @@@ sample end
}  // namespace
