#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記の単体テストでしているstd::vector<std::vector<XXX>>を、
// テンプレートエイリアスによって簡潔に記述せよ。

TEST(TemplateMetaProgrammingQ, template_alias)
{
    {
        auto vv = std::vector<std::vector<int>>{{1, 2, 3}, {3, 4, 5}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((std::vector<int>{1, 2, 3}), vv[0]);
        ASSERT_EQ((std::vector<int>{3, 4, 5}), vv[1]);
        ASSERT_EQ(5, vv[1][2]);
    }
    {
        auto vv = std::vector<std::vector<float>>{{1, 2, 3}, {3, 4, 5}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((std::vector<float>{1, 2, 3}), vv[0]);
        ASSERT_EQ((std::vector<float>{3, 4, 5}), vv[1]);
        ASSERT_EQ(5, vv[1][2]);
    }
    {
        auto vv = std::vector<std::vector<std::string>>{{"1", "2", "3"}, {"3", "4", "5"}};
        ASSERT_EQ(2, vv.size());
        ASSERT_EQ((std::vector<std::string>{"1", "2", "3"}), vv[0]);
        ASSERT_EQ((std::vector<std::string>{"3", "4", "5"}), vv[1]);
        ASSERT_EQ("5", vv[1][2]);
    }
}
// @@@ sample end
}  // namespace
