#include <algorithm>
#include <fstream>
#include <iterator>

#include "gtest_wrapper.h"

#include "isp_test_score_average.h"
#include "solid_ut.h"

using namespace Solid_UT;
using namespace Solid_ISP_A;

// @@@ sample begin 0:0

namespace {

TEST_F(SolidISP_A, TestScoreAverage)
{
    auto tsa = TestScoreAverage{test_score_org_};

    ASSERT_EQ(tsa.GetAverage("堂林"), 65);
    ASSERT_EQ(tsa.GetAverage("広輔"), 26);
    ASSERT_EQ(tsa.GetAverage("會澤"), 53);
    ASSERT_EQ(tsa.GetAverage("松山"), 73);
    ASSERT_EQ(tsa.GetAverage("菊池"), 50);
    ASSERT_EQ(tsa.GetAverage("鈴木"), 60);

    ASSERT_THROW(tsa.GetAverage("野村"), std::out_of_range);

    auto const exp = std::vector<std::string>{
        "松山", "堂林", "鈴木", "會澤", "菊池", "広輔",
    };

    ASSERT_EQ(tsa.DescendingOrder(), exp);
    ASSERT_EQ(tsa.DescendingOrder(), exp);  // キャッシュのテスト
}
}  // namespace
// @@@ sample end
