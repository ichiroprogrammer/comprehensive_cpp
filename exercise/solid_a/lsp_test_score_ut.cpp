#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>
#include <type_traits>

#include "gtest_wrapper.h"

#include "lsp_test_score.h"
#include "solid_ut.h"

using namespace Solid_UT;
using namespace Solid_LSP_A;

// @@@ sample begin 0:0

namespace {

// @@@ ignore begin

TEST_F(SolidLSP_A, TestScore_LoadCSV)
{
    auto ts = TestScore{};
    LoadCSV(test_score_org_, ts);

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
    };

    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

    auto exp_str = std::string{
        "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
        "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
    ASSERT_EQ(ToString(ts), exp_str);
}

std::string whole_file(std::string const& filename)
{
    auto ifs = std::ifstream{filename};

    return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
}

TEST_F(SolidLSP_A, TestScore_AddScore)
{
    auto ts = TestScore{};
    LoadCSV(test_score_org_, ts);

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

TEST_F(SolidLSP_A, TestScore_GetScore)
{
    auto ts = TestScore{};
    LoadCSV(test_score_org_, ts);

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

TEST_F(SolidLSP_A, TestScore_StoreCSV)
{
    auto ts = TestScore{};
    LoadCSV(test_score_org_, ts);
    StoreCSV(ts, test_score_act_);

    auto content_act = whole_file(test_score_act_);
    auto content_exp = whole_file(test_score_exp_);

    ASSERT_EQ(content_exp, content_act);

    // 不正ファイルロード
    auto ts2 = ts;
    ASSERT_THROW(LoadCSV(test_score_exp_err_, ts2), std::out_of_range);

    // エクセプション 強い保証
    ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
}

TEST_F(SolidLSP_A, TestScore_Average)
{
    auto ts = TestScore{};
    LoadCSV(test_score_org_, ts);

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

// @@@ ignore end

// [A]
// ファイルtest_score_org_には、TestScoreForceの不正値が含まれているため、
// 下記の単体テストでの、
//      LoadCSV(test_score_org_, ts_f);
// はエクセプションが発生するべきだが、実際にはパスしてしまう。
// 一方で、エクセプションが発生するようにLoadCSVを変更するには、LoadCVSの第2引数の
// ランタイム時の実際の型が必要になってしまうため、この解決手段にも問題がある。

TEST_F(SolidLSP_A, TestScoreForce_LoadCSV)
{
    auto ts_f = TestScoreForce{};
    LoadCSV(test_score_org_, ts_f);  // 本来はエクセプションが発生すべき。

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
    };

    ASSERT_TRUE(std::equal(ts_f.begin(), ts_f.end(), exp.begin()));

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
}

std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
{
    auto const csv_sep = std::regex{R"( *, *)"};
    auto       name    = std::string{};
    auto       score   = std::vector<int32_t>{};

    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end;
         ++it) {
        if (name.length() == 0) {
            name = *it;
        }
        else {
            auto s = std::stoi(*it);
            score.emplace_back(s);
        }
    }

    return {std::move(name), std::move(score)};
}

template <typename TEST_SCORE>
TEST_SCORE LoadCSV(std::string const& filename)
{
    static_assert(
        std::is_same_v<TEST_SCORE, TestScore> || std::is_same_v<TEST_SCORE, TestScoreForceFixed>);

    auto data = std::ifstream{filename};

    typename TEST_SCORE::ScoreAll_t test_score_raw;
    auto                            line = std::string{};
    while (std::getline(data, line)) {
        // std::pair<TestScore::ScoreAll_t::iterator, bool>
        auto ret = test_score_raw.insert(parse_line(line));
        assert(ret.second);
    }

    typename TEST_SCORE::ScoreOne_t one_test;
    for (auto const& pair : test_score_raw) {
        one_test.emplace_back(std::make_pair(pair.first, 0));
    }

    auto const score_count = test_score_raw.begin()->second.size();
    auto       ts          = TEST_SCORE{};

    for (auto i = 0U; i < score_count; ++i) {
        for (auto& pair : one_test) {
            pair.second = test_score_raw[pair.first][i];
        }
        ts.AddScore(one_test);
    }

    return ts;
}

TEST_F(SolidLSP_A, TestScoreForceFixed_LoadCSV)
{
    // 下で使用しているLoadCSVはtemplateで実装し直したもの(上記templace <>LoadCSV)。
    // 従来のLoadCSVでは型違いでコンパイルできない。
    // また、従来のLoadCSVは第2引数をTestScore&をしたため、
    // ここで指摘したような問題を引き起こしやすい。この問題を解決するため、
    // templace <>LoadCSVは引数での値戻しをやめ、リターンでの値戻しに改めた。
    ASSERT_THROW(LoadCSV<TestScoreForceFixed>(test_score_org_), std::out_of_range);

    TestScoreForceFixed ts_f_f = LoadCSV<TestScoreForceFixed>(test_score_org_f_);

    auto const exp = TestScore::ScoreAll_t{
        TestScore::ScoreAll_t::value_type("堂林", {0, 50, 80}),
        TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
        TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
        TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
        TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
        TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
    };

    ASSERT_TRUE(std::equal(ts_f_f.begin(), ts_f_f.end(), exp.begin()));
}
}  // namespace
// @@@ sample end
