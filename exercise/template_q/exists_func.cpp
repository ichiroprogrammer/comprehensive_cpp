#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// テンプレートパラメータの型がメンバ関数c_str()を持つか否かを判定する
// クラステンプレートhas_c_str<T>と定数テンプレートhas_c_str_v<T>を作れ。

namespace {

TEST(TemplateMetaProgrammingQ, has_c_str)
{
#if 0
    static_assert(has_c_str_v<std::string>);
    static_assert(!has_c_str_v<std::vector<int>>);
#endif
}
}  // namespace
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 範囲for文は、
//      for(auto a : obj ) { ... }
// のような形式で表現される。
// テンプレートパラメータから生成されたオブジェクトが、
// このobjに指定できるか否かを判定するクラステンプレートis_range<T>
// と定数テンプレートis_range_v<T>を作れ。

namespace {

TEST(TemplateMetaProgrammingQ, is_range)
{
#if 0
    static_assert(is_range_v<std::string>);
    static_assert(is_range_v<std::vector<int>>);
    static_assert(!is_range_v<std::mutex>);
    static_assert(!is_range_v<std::lock_guard<std::mutex>>);
#endif
}
}  // namespace
// @@@ sample end
