#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// 以下の仕様を満たすクラステンプレートis_same_some_of<T, U...>と
// 定数テンプレートis_same_some_of_v<T, U...>を作れ。
//  * 2個以上のテンプレートパラメータを持つ
//  * 第1パラメータと他のパラメータの何れかが同一の型であった場合、メンバvalueがtrueになる
//  * 前行の条件が成立しなかった場合、メンバvalueがfalseになる
//  * 型の同一性はstd::is_sameを使って判定する

namespace {

TEST(TemplateMetaProgrammingQ, is_same_some_of)
{
#if 0
    static_assert(!is_same_some_of_v<int, int8_t, int16_t, uint16_t>);
    static_assert(is_same_some_of_v<int, int8_t, int16_t, uint16_t, int32_t>);
    static_assert(is_same_some_of_v<int&, int8_t, int16_t, int32_t&, int32_t>);
    static_assert(!is_same_some_of_v<int&, int8_t, int16_t, uint32_t&, int32_t>);
    static_assert(is_same_some_of_v<std::string, int, char*, std::string>);
    static_assert(!is_same_some_of_v<std::string, int, char*>);
#endif
}
}  // namespace
// @@@ sample end
