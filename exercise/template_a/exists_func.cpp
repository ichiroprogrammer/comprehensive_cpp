#include <mutex>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// テンプレートパラメータの型がメンバ関数c_str()を持つか否かを判定する
// クラステンプレートhas_c_str<T>と定数テンプレートhas_c_str_v<T>を作れ。

template <typename T, typename U = bool>
struct has_c_str : std::false_type {
};

template <typename T>
struct has_c_str<T, decltype(std::declval<T>().c_str(), bool{})> : std::true_type {
};

template <typename T>
constexpr bool has_c_str_v{has_c_str<T>::value};

namespace {

TEST(TemplateMetaProgrammingA, has_c_str)
{
    static_assert(has_c_str_v<std::string>);
    static_assert(!has_c_str_v<std::vector<int>>);
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 範囲for文は、
//      for(auto a : obj ) { ... }
// のような形式で表現される。
// テンプレートパラメータから生成されたオブジェクトが、
// このobjに指定できるか否かを判定するクラステンプレートis_range<T>
// と定数テンプレートis_range_v<T>を作れ。

// 解説
// 上記objに指定できるための条件は、std::begin()、std::end()の引数になれることとした。
// セマンティクス的に正しいstd::begin()、std::end()は、それぞれが最初と最後を表す
// イテレータ(もしくはポインタ)でなければならないが、それはテンプレートでの判定の範囲外である。

template <typename, typename = bool>
struct exists_begin : std::false_type {
};

template <typename T>
struct exists_begin<T, decltype(std::begin(std::declval<T&>()), bool{})> : std::true_type {
};

template <typename T>
constexpr bool exists_begin_v{exists_begin<T>::value};

template <typename, typename = bool>
struct exists_end : std::false_type {
};

template <typename T>
struct exists_end<T, decltype(std::end(std::declval<T&>()), bool{})> : std::true_type {
};

template <typename T>
constexpr bool exists_end_v{exists_end<T>::value};

template <typename T>
struct is_range : std::conditional_t<exists_begin_v<T> && exists_end_v<T>, std::true_type, std::false_type> {
};

template <typename T>
constexpr bool is_range_v{is_range<T>::value};

namespace {

TEST(TemplateMetaProgrammingA, is_range)
{
    static_assert(is_range_v<std::string>);
    static_assert(is_range_v<std::vector<int>>);
    static_assert(!is_range_v<std::mutex>);
    static_assert(!is_range_v<std::lock_guard<std::mutex>>);
}
}  // namespace
// @@@ sample end
