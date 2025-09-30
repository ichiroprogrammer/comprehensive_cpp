#pragma once
#include <map>
#include <string>
#include <vector>

namespace Solid_LSP_Q {

// @@@ sample begin 0:0
// [Q]
// 下記クラスTestScoreが管理するテストのスコアの値は、
//      * 0～100   テストのスコア
//      *-1        未受験
//      * それ以外 不正値であるため、このデータを入力すると
//                 std::out_of_rangeエクセプションが発生する。
// を表すが、未受講を許可しない仕様(受験できない場合のスコアは0点)の
// TestScoreForceも必要になったため下記のように定義した。
//      * TestScoreForceが管理するテストのスコアの値は
//           * 0～100   テストのスコア
//           * それ以外 不正値であるため、このデータを入力すると
//                      std::out_of_rangeエクセプションが発生する。
//      * それ以外の動作はTestScoreと同じ。
//  これは、事前条件(「-1～100を受け入れる」から「0～100を受け入れる」)の強化であるため、
//  LSPに反する。
//  これにより起こる問題点を単体テストを用いて指摘せよ。
//
// [Q]
// 上記問題を解決するため、クラスTestScoreForceFixedを作り単体テストを行え。

class TestScore {
public:
    TestScore()                            = default;
    virtual ~TestScore()                   = default;
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
    virtual void validate_score(int32_t score) const;
    ScoreAll_t   test_score_row_{};
};

class TestScoreForce : public TestScore {
private:
    // int32_t score: 0～100はスコア、それ以外は不正データ
    virtual void validate_score(int32_t score) const override;
};

std::string           ToString(TestScore const& ts);
void                  LoadCSV(std::string const& filename, TestScore& test_score);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);
// @@@ sample end
}  // namespace Solid_LSP_Q
