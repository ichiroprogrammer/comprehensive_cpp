#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// 下記の仕様を満たす関数テンプレートis_void_f<T>と定数テンプレートis_void_f_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
//    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
//    * std::is_sameを使わない
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

template <typename T>
constexpr bool is_void_f() noexcept
{
    return false;
}

template <>
constexpr bool is_void_f<void>() noexcept
{
    return true;
}

template <typename T>
constexpr bool is_void_f_v{is_void_f<T>()};

namespace IsVoidTest {
void        test_func_0() noexcept {};
std::string test_func_1() { return "test"; };
}  // namespace IsVoidTest

namespace {

TEST(TemplateMetaProgrammingA, is_void_f)
{
    static_assert(!is_void_f_v<int>);
    static_assert(is_void_f_v<void>);
    static_assert(is_void_f_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_f_v<decltype(IsVoidTest::test_func_1())>);
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 下記の仕様を満たすクラステンプレートis_void_s<T>と定数テンプレートis_void_s_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
//    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
//    * std::is_sameを使わない
//    * std::true_type/std::false_typeを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

template <typename T>
struct is_void_s : std::false_type {
};

template <>
struct is_void_s<void> : std::true_type {
};

template <typename T>
constexpr bool is_void_s_v{is_void_s<T>::value};

namespace {

TEST(TemplateMetaProgrammingA, is_void_s)
{
    static_assert(!is_void_s_v<int>);
    static_assert(is_void_s_v<void>);
    static_assert(is_void_s_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_s_v<decltype(IsVoidTest::test_func_1())>);
}
}  // namespace
// @@@ sample end

// @@@ sample begin 2:0
// [A]
// 下記の仕様を満たす関数テンプレートis_void_sfinae_f<T>と
// 定数テンプレートis_void_sfinae_f<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
//    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
//    * std::is_sameを使わない
//    * SFINAEを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace Inner_ {

// T == void
template <typename T>
constexpr auto is_void_sfinae_f_detector(void const* v, T const* t) noexcept
    -> decltype(t = v, bool{})  // T != voidの場合、t = vはill-formed
                                // T == voidの場合、well-formedでbool型生成
{
    return true;
}

constexpr auto is_void_sfinae_f_detector(...) noexcept  // name lookupの順位は最低
{
    return false;
}
}  // namespace Inner_

template <typename T>
constexpr bool is_void_sfinae_f() noexcept
{
    return Inner_::is_void_sfinae_f_detector(nullptr, static_cast<T*>(nullptr));
}

template <typename T>
constexpr bool is_void_sfinae_f_v{is_void_sfinae_f<T>()};

namespace {

TEST(TemplateMetaProgrammingA, is_void_sfinae_f)
{
    static_assert(!is_void_sfinae_f_v<int>);
    static_assert(is_void_sfinae_f_v<void>);
    static_assert(is_void_sfinae_f_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_sfinae_f_v<decltype(IsVoidTest::test_func_1())>);
}
}  // namespace
// @@@ sample end

// @@@ sample begin 3:0
// [A]
// 下記の仕様を満たすクラステンプレートis_void_sfinae_s<T>と
// 定数テンプレートis_void_sfinae_s_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
//    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
//    * std::is_sameを使わない
//    * std::true_type/std::false_typeを利用する
//    * SFINAEを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace Inner_ {

template <typename T>
T*& t2ptr();

}  // namespace Inner_

template <typename T, typename = void*&>
struct is_void_sfinae_s : std::false_type {
};

template <typename T>
struct is_void_sfinae_s<T, decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())> : std::true_type {
};

template <typename T>
constexpr bool is_void_sfinae_s_v{is_void_sfinae_s<T>::value};

namespace {

TEST(TemplateMetaProgrammingA, is_void_sfinae_s)
{
    static_assert(!is_void_sfinae_s_v<int>);
    static_assert(is_void_sfinae_s_v<void>);
    static_assert(is_void_sfinae_s_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_sfinae_s_v<decltype(IsVoidTest::test_func_1())>);
}
}  // namespace
// @@@ sample end
