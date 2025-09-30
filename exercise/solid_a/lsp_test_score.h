#pragma once
#include <map>
#include <string>
#include <vector>

namespace Solid_LSP_A {

// @@@ sample begin 0:0
// [A]
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
// [A]
// 上記問題を解決するため、クラスTestScoreForceFixedを作り単体テストを行え。
//
// [解説]
// TestScoreForceFixedをTestScoreからprivate継承することで、
// TestScoreForceFixedとTestScorの関係がis-aの関係ではなくなるためLSPに適合する。
// 一方で、private継承の影響で、TestScoreForceFixedは、
//      * void LoadCSV(std::string const& filename, TestScore& test_score);
//      * void StoreCSV(TestScore const& test_score, std::string const& filename);
// 等TestScoreオブジェクトのリファレンスやポインタを受け取る関数が使えなくなる
// (そもそもそれが目的でprivate継承にした)。
// これに対処するために、オリジナルのコードをほとんどクローンした
//      * void LoadCSV(std::string const& filename, TestScoreForceFixed& test_score);
//      * void StoreCSV(TestScoreForceFixed const& test_score, std::string const& filename);
// を作ることは当然、誤りである。
// クローンを作らずに対処するためのコードを単体テストに記述したので参照してほしい。
// また、TestScoreForceを作ったことが根本的な誤りであった可能性もある。
// 「未受講データ-1を入力された場合、それをテストスコア0と解釈する」ようなオプションを
// TestScoreに持たせることも考慮すべきであった。

class TestScore {
    // @@@ ignore begin
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
    // @@@ ignore end
};

class TestScoreForce : public TestScore {
    // @@@ ignore begin
private:
    // int32_t score: 0～100はスコア、それ以外は不正データ
    virtual void validate_score(int32_t score) const override;
    // @@@ ignore end
};

class TestScoreForceFixed : TestScore {
public:
    TestScoreForceFixed()                                      = default;
    virtual ~TestScoreForceFixed()                             = default;
    TestScoreForceFixed(TestScoreForceFixed const&)            = default;
    TestScoreForceFixed& operator=(TestScoreForceFixed const&) = delete;
    TestScoreForceFixed& operator=(TestScoreForceFixed&&)      = default;

    using ScoreAll_t = TestScore::ScoreAll_t;
    using ScoreOne_t = TestScore::ScoreOne_t;

    using TestScore::AddScore;
    using TestScore::GetScore;

    using TestScore::begin;
    using TestScore::end;

private:
    // int32_t score: 0～100はスコア、それ以外は不正データ
    virtual void validate_score(int32_t score) const override;
};

std::string           ToString(TestScore const& ts);
void                  LoadCSV(std::string const& filename, TestScore& test_score);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);
// @@@ sample end
}  // namespace Solid_LSP_A
