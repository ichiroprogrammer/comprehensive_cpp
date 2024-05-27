#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記の単体テストでしているstd::vector<std::vector<XXX>>を、
// テンプレートエイリアスによって簡潔に記述せよ。

// 解説
// 下記のVect1Dはstd::vectorに対して簡潔な記述方法を提供しているとは言えないが、
// Vect2Dと同じような場面で使用することが明示されるため、ソースコードに一貫性を与える。

template <typename T>
using Vect2D = std::vector<std::vector<T>>;

template <typename T>
using Vect1D = std::vector<T>;

TEST(TemplateMetaProgrammingA, template_alias)
{
    {
        auto vv = Vect2D<int>{{1, 2, 3}, {3, 4, 5}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((Vect1D<int>{1, 2, 3}), vv[0]);
        ASSERT_EQ((Vect1D<int>{3, 4, 5}), vv[1]);
        ASSERT_EQ(5, vv[1][2]);
    }
    {
        auto vv = Vect2D<float>{{1, 2, 3}, {3, 4, 5}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((Vect1D<float>{1, 2, 3}), vv[0]);
        ASSERT_EQ((Vect1D<float>{3, 4, 5}), vv[1]);
        ASSERT_EQ(5, vv[1][2]);
    }
    {
        auto vv = Vect2D<std::string>{{"1", "2", "3"}, {"3", "4", "5"}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((Vect1D<std::string>{"1", "2", "3"}), vv[0]);
        ASSERT_EQ((Vect1D<std::string>{"3", "4", "5"}), vv[1]);
        ASSERT_EQ("5", vv[1][2]);
    }
}
// @@@ sample end
}  // namespace
