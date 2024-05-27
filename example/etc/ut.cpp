#include <algorithm>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0

TEST(UT, std_vector)
{
    auto v0 = std::vector{3, 2, 1};

    ASSERT_EQ(3, v0.size());
    ASSERT_EQ(3, v0[0]);
    ASSERT_EQ(2, v0[1]);
    ASSERT_EQ(1, v0[2]);
    ASSERT_THROW(v0.at(3), std::out_of_range);  // エクセプション発生

    // sortのテスト
    std::sort(v0.begin(), v0.end());
    ASSERT_EQ((std::vector{1, 2, 3}), v0);

    // transformのテスト
    auto v1 = std::vector<int>{};
    std::transform(v0.begin(), v0.end(), std::back_inserter(v1), [](auto x) { return x * 2; });
    ASSERT_EQ((std::vector{2, 4, 6}), v1);
}
// @@@ sample end
}  // namespace
