#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// 下記の仕様を満たす関数テンプレートis_void_f<T>と定数テンプレートis_void_f_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
//    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
//    * std::is_sameを使わない
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace IsVoidTest {
void        test_func_0() noexcept {};
std::string test_func_1() { return "test"; };
}  // namespace IsVoidTest

namespace {

TEST(TemplateMetaProgrammingQ, is_void_f)
{
#if 0
    static_assert(!is_void_f_v<int>);
    static_assert(is_void_f_v<void>);
    static_assert(is_void_f_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_f_v<decltype(IsVoidTest::test_func_1())>);
#endif
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 下記の仕様を満たすクラステンプレートis_void_s<T>と定数テンプレートis_void_s_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
//    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
//    * std::is_sameを使わない
//    * std::true_type/std::false_typeを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace {

TEST(TemplateMetaProgrammingQ, is_void_s)
{
#if 0
    static_assert(!is_void_s_v<int>);
    static_assert(is_void_s_v<void>);
    static_assert(is_void_s_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_s_v<decltype(IsVoidTest::test_func_1())>);
#endif
}
}  // namespace
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 下記の仕様を満たす関数テンプレートis_void_sfinae_f<T>と
// 定数テンプレートis_void_sfinae_f<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
//    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
//    * std::is_sameを使わない
//    * SFINAEを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace {

TEST(TemplateMetaProgrammingQ, is_void_sfinae_f)
{
#if 0
    static_assert(!is_void_sfinae_f_v<int>);
    static_assert(is_void_sfinae_f_v<void>);
    static_assert(is_void_sfinae_f_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_sfinae_f_v<decltype(IsVoidTest::test_func_1())>);
#endif
}
}  // namespace
// @@@ sample end

// @@@ sample begin 3:0
// [Q]
// 下記の仕様を満たすクラステンプレートis_void_sfinae_s<T>と
// 定数テンプレートis_void_sfinae_s_v<T>を作れ。
//    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
//    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
//    * std::is_sameを使わない
//    * std::true_type/std::false_typeを利用する
//    * SFINAEを利用する
//    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

namespace {

TEST(TemplateMetaProgrammingQ, is_void_sfinae_s)
{
#if 0
    static_assert(!is_void_sfinae_s_v<int>);
    static_assert(is_void_sfinae_s_v<void>);
    static_assert(is_void_sfinae_s_v<decltype(IsVoidTest::test_func_0())>);
    static_assert(!is_void_sfinae_s_v<decltype(IsVoidTest::test_func_1())>);
#endif
}
}  // namespace
// @@@ sample end
