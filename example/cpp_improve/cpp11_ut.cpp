#include <forward_list>
#include <regex>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "gtest_wrapper.h"

namespace {

TEST(cpp11, forward_list)
{
    // @@@ sample begin 0:0

    std::forward_list<int> fl{1, 2, 3};

    // 要素の挿入
    EXPECT_EQ(fl.front(), 1);
    fl.push_front(0);
    EXPECT_EQ(fl.front(), 0);

    auto it = fl.begin();
    EXPECT_EQ(*++it, 1);
    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*++it, 3);
    // @@@ sample end
}

// std::unordered_mapのテスト
TEST(cpp11, unordered_map)
{
    // @@@ sample begin 0:1

    std::unordered_map<int, std::string> umap;

    // 要素の挿入
    umap[1] = "one";
    umap[2] = "two";
    umap[3] = "three";

    // 要素の確認
    EXPECT_EQ(umap[1], "one");
    EXPECT_EQ(umap[2], "two");
    EXPECT_EQ(umap[3], "three");

    // 存在確認
    EXPECT_NE(umap.find(1), umap.end());
    EXPECT_EQ(umap.find(4), umap.end());
    // @@@ sample end
}

// std::unordered_setのテスト
TEST(cpp11, unordered_set)
{
    // @@@ sample begin 0:2

    std::unordered_set<int> uset{1, 2, 3};

    // 要素の挿入
    uset.insert(4);
    uset.insert(5);

    // 存在確認
    EXPECT_NE(uset.find(1), uset.end());
    EXPECT_NE(uset.find(4), uset.end());
    EXPECT_EQ(uset.find(6), uset.end());

    // サイズの確認
    EXPECT_EQ(uset.size(), 5);
    // @@@ sample end
}

// std::type_indexのテスト
TEST(cpp11, type_index)
{
    // @@@ sample begin 0:3

    std::unordered_map<std::type_index, std::string> type_map;

    // std::type_indexを使って型をキーとしてマッピング
    type_map[typeid(int)]         = "int";
    type_map[typeid(double)]      = "double";
    type_map[typeid(std::string)] = "string";

    // マッピングの確認
    EXPECT_EQ(type_map[typeid(int)], "int");
    EXPECT_EQ(type_map[typeid(double)], "double");
    EXPECT_EQ(type_map[typeid(std::string)], "string");

    // 存在しない型の確認
    EXPECT_EQ(type_map.find(typeid(float)), type_map.end());
    // @@@ sample end
}
}  // namespace
