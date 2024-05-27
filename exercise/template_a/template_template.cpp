#include <list>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// 以下の仕様を満たすクラステンプレートを作れ。
//  * 任意のSTLコンテナを唯一のテンプレートパラメータとする
//  * そのコンテナを使用しint型のデータを格納する

template <template <class...> class STL_CONTAINER>
struct IntContainer : STL_CONTAINER<int> {
    using STL_CONTAINER<int>::STL_CONTAINER;
};

namespace {

TEST(TemplateMetaProgrammingA, template_template)
{
    auto vi = IntContainer<std::vector>{1, 2, 3};
    auto vl = IntContainer<std::list>{1, 2, 3};
    auto vs = IntContainer<std::basic_string>{1, 2, 3};  // 意味は不明だがこれも可能

    ASSERT_EQ((std::vector<int>{1, 2, 3}), vi);
    ASSERT_EQ((std::list<int>{1, 2, 3}), vl);
    ASSERT_EQ((std::basic_string<int>{1, 2, 3}), vs);
}
}  // namespace
// @@@ sample end
