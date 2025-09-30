#pragma once
#include <map>
#include <string>
#include <vector>

namespace Solid_OCP_A {

// @@@ sample begin 0:0
// [A]
// 下記クラスTestScoreは、
//      * テスト受講者とその点数を保持/提供する。
//      * テスト受講者とその点数をCSVファイルからロードする。
// 責任を持つ。サポートするファイル形式が増えた場合、このクラスを修正せざるを得ないため、
// 機能拡張に対して開いていない。つまり、OCPに反していると言える
// (実際にはこの程度の違反が問題になることは稀である)。
//
// サポートしているファイル形式はCSVのみであったが、TSVを追加することになった。
// 今後もサポートするファイル形式を増やす必要があるため、OCPに従った方が良いと判断し、
// TestScoreの責務から「ファイルのロード」を外し、その機能を外部関数として定義することにした。
// これに従い、下記クラスTestScoreを修正し、外部関数
//      void LoadCSV(std::string const& filename, TestScore& test_score);
// を作り、単体テストを行え。

class TestScore {
public:
    TestScore()                            = default;
    TestScore(TestScore const&)            = default;
    TestScore& operator=(TestScore const&) = delete;
    TestScore& operator=(TestScore&&)      = default;  // moveが必要になった

    // @@@ ignore begin
    using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
    using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

    void                        AddScore(ScoreOne_t const& one_test_score);
    std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }
    // @@@ ignore end

    // void LoadCSV(std::string const& filename);
    // は外部関数にした。

    ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
    ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

private:
    // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
    void       validate_score(int32_t score) const;
    ScoreAll_t test_score_row_{};
};

std::string           ToString(TestScore const& ts);
void                  LoadCSV(std::string const& filename, TestScore& test_score);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);
// @@@ sample end
}  // namespace Solid_OCP_A
