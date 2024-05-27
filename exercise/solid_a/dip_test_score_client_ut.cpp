#include "gtest_wrapper.h"

#include "dip_test_score_client.h"
#include "solid_ut.h"

using namespace Solid_UT;
using namespace Solid_DIP_A;

// @@@ sample begin 0:0

// 演習コードと同一であるため省略
// @@@ ignore begin

namespace {

TEST_F(SolidDIP_A, TestStoreClient_LoadAsync)
{
    auto tsc = TestScoreClient{};

    tsc.LoadAsync("../ut_data2/test_score_org.csv");

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
    };

    // ここで何か別のことをして終わったら
    tsc.Wait();

    auto const& ts = tsc.GetTestScore();

    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

    auto const exp_str = std::string{
        "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
        "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
    ASSERT_EQ(ToString(ts), exp_str);
}
}  // namespace
// @@@ ignore end

// @@@ sample end
