#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <concepts>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace FuncReturnAuto {

// @@@ sample begin 0:0

auto f(int32_t a, int32_t b) noexcept -> decltype(a + b)  // NG
{
    return a + b;
}

template <typename T>
auto f(T a, T b) noexcept -> decltype(a + b)  // OK 後置構文以外に方法がない
{
    return a + b;  // T = uint8_tとすると、a + bの型はint32_t
}
// @@@ sample end
}  // namespace FuncReturnAuto

namespace FuncReturnMulti {
// @@@ sample begin 1:0

// NG 関数の戻り値が不明確
void f(int32_t a, int32_t b, int32_t& quotient, int32_t& remainder)
{
    quotient  = a / b;
    remainder = a % b;
}

// NG 関数の戻り値が不明確
int32_t f(int32_t a, int32_t b, int32_t& remainder)
{
    remainder = a % b;
    return a / b;
}

// 場合によりNG  f_pairがprivate関数やファイル内関数であり、広域に使われないのであれば問題ない
std::pair<int32_t, int32_t> f_pair(int32_t a, int32_t b) { return {a / b, a % b}; }

// 場合によりNG  f_tupleがprivate関数やファイル内関数であり、広域に使われないのであれば問題ない
//               f_tupleが広域に使われない場合でも、tupleの型引数の数が3個を大きく超える場合に可読性が劣化する
std::tuple<int32_t, int32_t> f_tuple(int32_t a, int32_t b) { return {a / b, a % b}; }

struct Result {
    int32_t quotient;
    int32_t remainder;
};

Result f_struct(int32_t a, int32_t b)  // OK
{
    return {a / b, a % b};
}
// @@@ sample end

TEST(ProgrammingConvention, return_pair)
{
    // clang-format off
    // @@@ sample begin 1:1

    int32_t quotient0;
    int32_t remainder0;
    f(7, 3, quotient0, remainder0);             // NG quotient0、remainder0が戻り値かどうかわかりづらい
    ASSERT_EQ(2, quotient0);
    ASSERT_EQ(1, remainder0);

    int32_t remainder1;
    int32_t quotient1 = f(7, 3, remainder1);    // NG remainder1が戻り値かどうかわかりづらい
    ASSERT_EQ(2, quotient1);
    ASSERT_EQ(1, remainder1);

    auto ret0 = f_pair(7, 3);                   // 場合によりNG
    ASSERT_EQ(2, ret0.first);                   // ret0.firstが何を表しているかどうかわかりづらい
    ASSERT_EQ(1, ret0.second);                  // ret0.secondが何を表しているかどうかわかりづらい

    auto ret1 = f_tuple(7, 3);                  // 場合によりNG
    ASSERT_EQ(2, std::get<0>(ret1));            // std::get<0>(ret1)が何を表しているかどうかわかりづらい
    ASSERT_EQ(1, std::get<1>(ret1));            // std::get<1>(ret1)が何を表しているかどうかわかりづらい

    auto [quotient2, remainder2] = f_struct(7, 3); // OK C++17 構造化束縛の使いすぎには注意
    ASSERT_EQ(2, quotient2);
    ASSERT_EQ(1, remainder2);

    auto ret2 = f_struct(7, 3);                 // OK
    ASSERT_EQ(2, ret2.quotient);
    ASSERT_EQ(1, ret2.remainder);
    // @@@ sample end
    // clang-format on
}
}  // namespace FuncReturnMulti

// @@@ sample begin 2:0

namespace {

// NG 関数の戻り値が不明確
bool f(int32_t a, int32_t b, int32_t& remainder)
{
    if (b == 0) {
        return false;
    }

    remainder = a % b;

    return true;
}

// NG 余りが-1になる場合(外れ値)、エラー通知
int32_t f(uint32_t a, uint32_t b)
{
    if (b == 0) {
        return -1;
    }

    return a % b;
}

// NG ret.firstがエラーを表していることが不明確
std::pair<bool, int32_t> f_pair(int32_t a, int32_t b)
{
    if (b == 0) {
        return {false, 0};
    }

    return {true, a % b};
}

struct Result {
    bool    is_success;
    int32_t remainder;
};

// NG 悪くはないが、エラー時でもResult::remainderにアクセスできる
Result f_struct(int32_t a, int32_t b)
{
    if (b == 0) {
        return {false, 0};
    }

    return {true, a % b};
}

std::optional<int32_t> f_optional(int32_t a, int32_t b)  // OK
{
    if (b == 0) {
        return std::nullopt;
    }

    return a % b;
}
// @@@ sample end
TEST(ProgrammingConvention, return_optional)
{
    // clang-format off
    // @@@ sample begin 2:1

    int32_t remainder0;

    auto result0 = f(7, 0, remainder0);             // NG エラー時にremainder0が有効か否かわからない
    ASSERT_FALSE(result0);

    auto remainder1 = f(7, 0);                      // NG エラー通知がわかりづらい
    ASSERT_EQ(-1, remainder1);

    auto ret = f_pair(7, 0);                        // NG ret.firstがエラーを表していることが不明確
    ASSERT_FALSE(ret.first);

    auto [result2, remainder2] = f_struct(7, 0);    // エラー時にremainder2が有効か否かわからない
    ASSERT_FALSE(result2);

    auto result1 = f_optional(7, 0);                // OK
    ASSERT_FALSE(result1);                          // エラーの判定  値は取り出すための*result1はエクセプション

    result1 = f_optional(7, 4);                     // OK
    ASSERT_TRUE(result1);                           // 成功の判定
    ASSERT_EQ(3, *result1);                         // 成功時の値取り出し
    // @@@ sample end
    // clang-format off
}
}  // namespace
