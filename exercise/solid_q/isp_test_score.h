#pragma once
#include <map>
#include <string>
#include <vector>

namespace Solid_ISP_Q {

// @@@ sample begin 0:0
// [Q]
// 下記クラスTestScoreの管理データの内、受験者とその平均スコア、
// 平均スコアの高い順でソートされた受験者リストを扱うクラスが必要になったため、
// 下記のようにイミュータブルなクラスTestScoreAverageを作成した。
//
// 現在のファイル構成では、TestScoreAverageのみを使うクラスや関数にも、
// このファイル全体への依存を強いる(つまり、TestScoreやLoadCSV等に依存させる)ため、
// ISPに反する。
// TestScoreAverageを使うクラスや関数に余計な依存関係が発生しないようにリファクタリングを
// 行え。

class TestScore {
public:
    TestScore()                            = default;
    TestScore(TestScore const&)            = default;
    TestScore& operator=(TestScore const&) = delete;
    TestScore& operator=(TestScore&&)      = default;

    using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
    using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

    void                        AddScore(ScoreOne_t const& one_test_score);
    std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

    ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
    ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

private:
    // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
    void       validate_score(int32_t score) const;
    ScoreAll_t test_score_row_{};
};

std::string           ToString(TestScore const& ts);
TestScore             LoadCSV(std::string const& filename);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);

class TestScoreAverage {
public:
    explicit TestScoreAverage(std::string const& filename);
    uint32_t                        GetAverage(std::string const& name) const;
    std::vector<std::string> const& DescendingOrder() const;

private:
    TestScore::ScoreOne_t const      average_;
    mutable std::vector<std::string> desending_order_{};
};
// @@@ sample end
}  // namespace Solid_ISP_Q
