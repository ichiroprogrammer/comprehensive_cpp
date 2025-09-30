#pragma once
#include <map>
#include <string>
#include <vector>

namespace Solid_SRP_A {

// @@@ sample begin 0:0
// [A]
// 下記クラスTestScoreはメンバにする必要のない関数までメンバにしてるため、
// インターフェースが肥大化してしまい、少なくともSRPに反している。
// メンバにする必要のないStoreCSVを外部関数にせよ。
// また、受験者の平均点を求める
//      TestScore::ScoreOne_t Average(TestScore const& test_score);
// を同様の方法で作り、単体テストを行え。

class TestScore {
public:
    // @@@ ignore begin
    TestScore()                            = default;
    TestScore(TestScore const&)            = default;
    TestScore& operator=(TestScore const&) = delete;

    using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
    using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

    void                        AddScore(ScoreOne_t const& one_test_score);
    std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }
    // @@@ ignore end

    // void StoreCSV(std::string const& filename) const;
    // は外部関数にした。
    void LoadCSV(std::string const& filename);

    // @@@ ignore begin
    ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
    ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

private:
    // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
    void       validate_score(int32_t score) const;
    ScoreAll_t test_score_row_{};
    // @@@ ignore end
};

std::string           ToString(TestScore const& ts);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);
// @@@ sample end
}  // namespace Solid_SRP_A
