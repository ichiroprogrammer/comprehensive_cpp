#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記関数ColorMask2Strはuint32_t型のビットマスクを引数に取る。
// これはユーザが使用間違いを起こしやすい脆弱なインターフェースである。
// enumによるビットマスク表現を使用しこの問題に対処せよ。

constexpr auto COLOR_RED    = 0b0001U;
constexpr auto COLOR_YELLOW = 0b0010U;
constexpr auto COLOR_GREEN  = 0b0100U;
constexpr auto COLOR_BLUE   = 0b1000U;

std::string ColorMask2Str(uint32_t color)
{
    auto ret = std::string{};

    if (COLOR_RED & color) {
        ret += "RED";
    }
    if (COLOR_YELLOW & color) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "YELLOW";
    }
    if (COLOR_GREEN & color) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "GREEN";
    }
    if (COLOR_BLUE & color) {
        if (ret.size() != 0) {
            ret += ',';
        }
        ret += "BLUE";
    }

    return ret;
}

TEST(DesignPatternQ, EnumBitmask)
{
    ASSERT_EQ("RED", ColorMask2Str(COLOR_RED));
    ASSERT_EQ("RED,YELLOW", ColorMask2Str(COLOR_RED | COLOR_YELLOW));
    ASSERT_EQ("YELLOW", ColorMask2Str(COLOR_YELLOW));
    ASSERT_EQ("YELLOW,GREEN,BLUE", ColorMask2Str(COLOR_YELLOW | COLOR_GREEN | COLOR_BLUE));

    ASSERT_EQ("", ColorMask2Str(0b10000));  // 想定していない使用法
}
// @@@ sample end
}  // namespace
