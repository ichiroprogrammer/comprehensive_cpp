#pragma once
#include <memory>
#include <string>
#include <vector>

namespace Solid_ISP_A {

// @@@ sample begin 0:0
// [A]
// 下記クラスTestScoreの管理データの内、受験者とその平均スコア、
// 平均スコアの高い順でソートされた受験者リストを扱うクラスが必要になったため、
// 下記のようにイミュータブルなクラスTestScoreAverageを作成した。
//
// 現在のファイル構成では、TestScoreAverageのみを使うクラスや関数にも、
// このファイル全体への依存を強いる(つまり、TestScoreやLoadCSV等に依存させる)ため、
// ISPに反する。
// TestScoreAverageを使うクラスや関数に余計な依存関係が発生しないようにリファクタリングを
// 行え。

// [解説]
// TestScoreAverageの宣言・定義をsolid_isp_test_score_a.hからこのファイルに移動し、
// TestScoreAverageのTestScore依存部分をTestScoreAverageDataで隠蔽することで、
// このファイルからのsolid_isp_test_score_a.hの依存を消した。
// また、TestScoreAverageのTestScore依存部はすべてsolid_isp_test_score_average_a.cppに移動した。
// これにより、TestScoreAverageの利用者はTestScoreに依存しなくなった。
//

class TestScoreAverage {
public:
    explicit TestScoreAverage(std::string const& filename);
    ~TestScoreAverage();
    uint32_t                        GetAverage(std::string const& name) const;
    std::vector<std::string> const& DescendingOrder() const;

private:
    struct TestScoreAverageData;
    std::unique_ptr<TestScoreAverageData> const data_;
};
// @@@ sample end
}  // namespace Solid_ISP_A
