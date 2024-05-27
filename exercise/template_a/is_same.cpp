#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// 以下の仕様を満たすクラステンプレートis_same_some_of<T, U...>と
// 定数テンプレートis_same_some_of_v<T, U...>を作れ。
//  * 2個以上のテンプレートパラメータを持つ
//  * 第1パラメータと他のパラメータの何れかが同一の型であった場合、メンバvalueがtrueになる
//  * 前行の条件が成立しなかった場合、メンバvalueがfalseになる
//  * 型の同一性はstd::is_sameを使って判定する

template <typename T, typename U, typename... Us>
struct is_same_some_of {
    static constexpr bool value{std::is_same_v<T, U> ? true : is_same_some_of<T, Us...>::value};
};

template <typename T, typename U>
struct is_same_some_of<T, U> {
    static constexpr bool value{std::is_same_v<T, U>};
};

template <typename T, typename U, typename... Us>
constexpr bool is_same_some_of_v{is_same_some_of<T, U, Us...>::value};

namespace {

TEST(TemplateMetaProgrammingA, is_same_some_of)
{
    static_assert(!is_same_some_of_v<int, int8_t, int16_t, uint16_t>);
    static_assert(is_same_some_of_v<int, int8_t, int16_t, uint16_t, int32_t>);
    static_assert(is_same_some_of_v<int&, int8_t, int16_t, int32_t&, int32_t>);
    static_assert(!is_same_some_of_v<int&, int8_t, int16_t, uint32_t&, int32_t>);
    static_assert(is_same_some_of_v<std::string, int, char*, std::string>);
    static_assert(!is_same_some_of_v<std::string, int, char*>);
}
}  // namespace
// @@@ sample end
