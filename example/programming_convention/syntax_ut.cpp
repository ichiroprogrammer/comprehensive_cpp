#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace CompoundStatementSample {

void f(int32_t a) noexcept
{
    volatile int32_t b;  // 変数をvolatile にしたのはscan-build対策
    int32_t          c[10];

    // @@@ sample begin 0:0

    if (a == 0) {
        b = 0;  // OK
    }

    // clang-format off
    if (a == 0)
        b = 0;                      // NG 複合文でない

    if (a == 0) {
        b = 0;                      // OK
    }
    else                            // NG 複合文でない
        b = 1;

    for (auto i = 0; i < a; ++i) {  // OK
        c[i] = i;
    }

    for (auto i = 0; i < a; ++i)    // NG
        c[i] = i;
    // @@@ sample end
    // clang-format on
    IGNORE_UNUSED_VAR(a, b, c);
}

volatile bool volatile_flag;

void f() noexcept
{
    // @@@ sample begin 0:1

    while (volatile_flag) {
    }  // NG ;が無い

    while (volatile_flag) {
        ;  // OK
    }

    while (volatile_flag)
        ;  // NG whileの文が複合文でない
    // @@@ sample end
}
}  // namespace CompoundStatementSample

namespace SwitchStatementSample {
int32_t f(int32_t a) noexcept
{
    auto b = 0;
    auto c = 0;
    auto d = 0;
    auto e = 0;

    SUPPRESS_WARN_GCC_BEGIN;
    SUPPRESS_WARN_GCC_FALLTHROUGH;

    // @@@ sample begin 1:0

    switch (a) {
    case 0:
        b = 0;
        break;  // OK
    case 1:
        e = 2;  // NG break無しで抜けているのにコメントが無い
    case 2:
        c = 1;
        // fallthrough  C++14以前であればOK
    case 3:
        e += 2;
        [[fallthrough]];  // OK C++17
    case 4:
        d = 1;
        break;  // OK
    default:
        assert(false);  // OK 論理的にここには来ないのならば、defaultを省略せずにassert
    }
    // @@@ sample end

    SUPPRESS_WARN_GCC_END;

    return b + c + d + e;
}
}  // namespace SwitchStatementSample

namespace IfStatementSample {

void f(int32_t a) noexcept
{
    // @@@ sample begin 2:0

    if (a == 1) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else if (a == 2) {
        // @@@ ignore begin
        // @@@ ignore end
    }  // NG elseで終了していない

    if (a == 1) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else if (a == 2) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else {  // OK else文でやることがない場合は、;のみ記述
        ;
    }
    // @@@ sample end
    // @@@ sample begin 2:1

    if (a == 1) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else if (a == 2) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else {              // OK
        assert(false);  //    ここに来るのはバグの場合。
    }
    // @@@ sample end
}
}  // namespace IfStatementSample

namespace ForStatementSample {

TEST(ProgrammingConvention, synstax_for)
{
    // @@@ sample begin 3:0

    auto vect = std::vector<uint32_t>{0, 1, 2, 3, 4};

    // NG oldスタイル
    for (auto i = 0U; i < vect.size(); ++i) {
        std::cout << vect[i] << " ";
    }
    // @@@ ignore begin
    std::cout << std::endl;
    // @@@ ignore end

    // NG C++03スタイル
    for (std::vector<uint32_t>::iterator it = vect.begin(); it != vect.end(); ++it) {
        *it = 3;
    }

    for (std::vector<uint32_t>::const_iterator it = vect.cbegin(); it != vect.cend(); ++it) {
        std::cout << *it << " ";
    }
    // @@@ ignore begin
    std::cout << std::endl;
    // @@@ ignore end

    // OK C++11スタイル
    for (auto const& a : vect) {
        std::cout << a << " ";
    }
    // @@@ ignore begin
    std::cout << std::endl;
    // @@@ ignore end
    // @@@ sample end
}
}  // namespace ForStatementSample

namespace ReturnSample {

int32_t f(bool xxx) noexcept
{
    // @@@ sample begin 4:0

    // @@@ ignore begin

    int32_t retval{1};
    int32_t retval2{0};

    // @@@ ignore end

    if (xxx) {
        // decltype(retval)は、int32_t
        // decltype((retval))は、(retval)がlvalueであるためint32_t&
        // この違いは通常問題にはならないが、関数の戻り値を型推測させると問題になる。
        return (retval);  // NG ()は不要
    }
    else {
        return retval2;  // OK
    }
    // @@@ sample end
}

// @@@ sample begin 4:1

// @brief メッセージを出力してプログラムを終了させる。
// @param const char* message 上記メッセージ
[[noreturn]] void terminate(char const* message)
{
    auto const str = std::string{"unrecoverable error"} + message;

    // @@@ ignore begin
    // @@@ ignore end

    throw std::runtime_error{str};
}
// @@@ sample end
}  // namespace ReturnSample

namespace LambdaSample {

std::vector<std::string>::const_iterator n_greater_5(std::vector<std::string> const& strs)
{
    // @@@ sample begin 5:0

    // ラムダ式はワンライナーが基本
    auto itr = std::find_if(strs.begin(), strs.end(), [](auto const& n) noexcept {
        return (n.at(0) == 'n') && (n.size() > 5);
    });
    // @@@ sample end

    return itr;
}

namespace {
TEST(ProgrammingConvention, synstax_lambda_1)
{
    auto d = std::vector<std::string>{"tako", "ika", "nama", "namako", "hitode"};
    auto n = n_greater_5(d);

    ASSERT_EQ("namako", *n);
}
}  // namespace
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_PARAM;

namespace NotRecommended {

// @@@ sample begin 5:1

// NG デフォルトのキャプチャ方式
class A {
public:
    // @@@ ignore begin
    explicit A(std::vector<std::string>&& strs) noexcept : strs_{std::move(strs)} {}
    // @@@ ignore end
    std::vector<std::string> GetNameLessThan(uint32_t length) const
    {
        auto ret = std::vector<std::string>{};

#if __cplusplus == 201703L  // =でのキャプチャは範囲は大きすぎるため、C++20から非推奨
        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [=](auto const& str) noexcept { return (strs_.size() < length); });

#elif __cplusplus == 202002L
        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [&strs = strs_, length = length](auto const& str) noexcept {
                         return (strs.size() < length);
                     });
#else
        static_assert(false, "C++ version not supported!");
#endif

        return ret;
    }

private:
    std::vector<std::string> strs_;
};
// @@@ sample end
SUPPRESS_WARN_END;
}  // namespace NotRecommended

namespace Recommended {
#define CPP_VER 14
// @@@ sample begin 5:2

// OK 限定したキャプチャにより、ラムダ式から可視である変数が限定された
class A {
public:
    // @@@ ignore begin
    explicit A(std::vector<std::string>&& strs) noexcept : strs_{std::move(strs)} {}
    // @@@ ignore end
    std::vector<std::string> GetNameLessThan(uint32_t length) const
    {
        auto ret = std::vector<std::string>{};

#if __cplusplus == 201103L  // c++11
                            // [length]を代入キャプチャと呼ぶ。

        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [length](std::string const& str) noexcept { return (str.size() < length); });

#elif __cplusplus >= 201402L  // c++14以降
        // [length = length]を初期化キャプチャと呼ぶ。
        // 左のlengthのスコープはラムダ式内。右のlengthのスコープはGetNameLessThan内。

        std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                     [length = length](auto const& str) noexcept { return (str.size() < length); });
#else
        static_assert(false, "CPP_VER should be 11 or 14");
#endif
        return ret;
    }
    // @@@ ignore begin
private:
    std::vector<std::string> strs_;
    // @@@ ignore end
};
// @@@ sample end

// @@@ sample begin 5:3

class B {
public:
    // @@@ ignore begin
    B(int min) noexcept : min_{min} {}
    // @@@ ignore end
    std::function<bool(int)> GenLambda(int max)
    {
        // NG
        // この関数が返すはクロージャがリファレンスしているmaxはこの関数が終了すると無効になる。
        return [&max](int n) noexcept { return n < max; };
    }

    std::function<bool(int)> GenLambda()
    {
        // NG
        // この関数が返すクロージャがリファレンスしているmin_はBオブジェクトが終了すると無効になる。
        return [&min = min_](int n) noexcept { return n > min; };
    }

private:
    int min_;
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, synstax_lambda_2)
{
    auto d = std::vector<std::string>{"tako", "ika", "nama", "namako", "hitode"};
    auto a = A{std::move(d)};

    auto ret = a.GetNameLessThan(5);

    for (auto const& str : ret) {
        std::cout << str << std::endl;
    }

    // @@@ sample begin 5:4

    auto square1 = [](int32_t n) { return n * n; };

    static_assert(square1(2) == 4);  // C++17以降、square1(2)はリテラル

    auto i = 2;
    // static_assert(square1(i) == 2);  // iはconstexprではないので、コンパイルエラー

    constexpr auto j       = 2;
    constexpr auto square2 = [n = j]() { return n * n; };  // constexprの宣言が必要

    static_assert(square2() == 4);  // C++17以降、square2()はリテラル

    auto square3 = [n = j]() { return n * n; };

    // static_assert(square3() == 4);  // square3()はリテラルではないので、コンパイルエラー
    // @@@ sample end

    IGNORE_UNUSED_VAR(i, square3);
}
// @@@ sample begin 5:5

constexpr int32_t square4(int32_t n)  // OK nがconstexprであれば、ラムダはconstexpr
{
    return [n] { return n * n; }();
}

static_assert(square4(2) == 4);  // C++17以降、square4(2)はリテラル

constexpr auto square5(int32_t n)  //  OK nがconstexprであれば、ラムダはconstexpr
{
    // nがconstexprならば、ラムダ式はリテラル
    auto f = [n] { return n * n; };

    // fの戻り値がリテラルならば、gもリテラル
    auto g = [f] { return f(); };
    return g;
}

static_assert(square5(2)() == 4);  // C++17以降、square5(2)はリテラル
// @@@ sample end

}  // namespace
}  // namespace Recommended
}  // namespace LambdaSample

namespace StatementInMacroSample {

// @@@ sample begin 6:0

// do-while(0)イデオムによる関数型マクロ
#define INIT_ARRAY(array_, x_)      \
    do {                            \
        for (auto& a_ : (array_)) { \
            a_ = (x_);              \
        }                           \
    } while (0)

void f(uint32_t (&a)[10])
{
    // INIT_ARRAYがdo-whileではなく、単なるブロックで囲むと、";"が余計になる。
    INIT_ARRAY(a, 3);
}
// @@@ sample end
}  // namespace StatementInMacroSample
