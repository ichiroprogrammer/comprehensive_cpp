#include <algorithm>
#include <fstream>
#include <iterator>

#include "gtest_wrapper.h"

#include "solid_ut.h"
#include "srp_test_score.h"

using namespace Solid_UT;
using namespace Solid_SRP_A;

// @@@ sample begin 0:0

namespace {

// @@@ ignore begin
TEST_F(SolidSRP_A, TestScore_LoadCSV)
{
    auto ts = TestScore{};
    ts.LoadCSV(test_score_org_);

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
    };

    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

    auto const exp_str = std::string{
        "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
        "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
    ASSERT_EQ(ToString(ts), exp_str);
}

std::string whole_file(std::string const& filename)
{
    auto ifs = std::ifstream{filename};

    return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
}

TEST_F(SolidSRP_A, TestScore_AddScore)
{
    auto ts = TestScore{};
    ts.LoadCSV(test_score_org_);

    auto const one_score = TestScore::ScoreOne_t{
        TestScore::ScoreOne_t::value_type("堂林", 50),
        TestScore::ScoreOne_t::value_type("広輔", 40),
        TestScore::ScoreOne_t::value_type("會澤", 70),
        TestScore::ScoreOne_t::value_type("松山", 1),
        TestScore::ScoreOne_t::value_type("菊池", -1),
        TestScore::ScoreOne_t::value_type("鈴木", 5),
        TestScore::ScoreOne_t::value_type("田中", 100),
        TestScore::ScoreOne_t::value_type("西川", 90),
    };

    ts.AddScore(one_score);

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
        TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
        TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
    };

    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

    auto const one_score_err = TestScore::ScoreOne_t{
        TestScore::ScoreOne_t::value_type("野村", -2),
        TestScore::ScoreOne_t::value_type("衣笠", 40),
    };

    // 不正データロード
    auto ts2 = ts;
    ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

    // エクセプション 強い保証
    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
}

TEST_F(SolidSRP_A, TestScore_GetScore)
{
    auto ts = TestScore{};
    ts.LoadCSV(test_score_org_);

    auto const& score_0 = ts.GetScore("堂林");
    ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

    auto const& score_1 = ts.GetScore("広輔");
    ASSERT_EQ((std::vector{40, 30, 10}), score_1);

    auto const& score_2 = ts.GetScore("會澤");
    ASSERT_EQ((std::vector{30, 60, 70}), score_2);

    auto const& score_3 = ts.GetScore("松山");
    ASSERT_EQ((std::vector{80, 90, 50}), score_3);

    auto const& score_4 = ts.GetScore("菊池");
    ASSERT_EQ((std::vector{50, 20, 80}), score_4);

    auto const& score_5 = ts.GetScore("鈴木");
    ASSERT_EQ((std::vector{0, 80, 100}), score_5);

    ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
}
// @@@ ignore end

TEST_F(SolidSRP_A, TestScore_StoreCSV)
{
    auto ts = TestScore{};
    ts.LoadCSV(test_score_org_);
    StoreCSV(ts, test_score_act_);

    auto content_act = whole_file(test_score_act_);
    auto content_exp = whole_file(test_score_exp_);

    ASSERT_EQ(content_exp, content_act);

    // 不正ファイルロード
    auto ts2 = ts;
    ASSERT_THROW(ts.LoadCSV(test_score_exp_err_), std::out_of_range);

    // エクセプション 強い保証
    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
}

TEST_F(SolidSRP_A, TestScore_Average)
{
    auto ts = TestScore{};
    ts.LoadCSV(test_score_org_);

    auto const exp = TestScore::ScoreOne_t{
        TestScore::ScoreOne_t::value_type("堂林", 65),
        TestScore::ScoreOne_t::value_type("広輔", 26),
        TestScore::ScoreOne_t::value_type("會澤", 53),
        TestScore::ScoreOne_t::value_type("松山", 73),
        TestScore::ScoreOne_t::value_type("菊池", 50),
        TestScore::ScoreOne_t::value_type("鈴木", 60),
    };
    auto act = Average(ts);

    ASSERT_EQ(act, exp);
}
}  // namespace
// @@@ sample end
