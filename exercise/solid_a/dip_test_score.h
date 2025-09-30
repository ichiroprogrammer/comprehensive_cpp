#pragma once
#include <future>
#include <map>
#include <string>
#include <vector>

namespace Solid_DIP_A {

// @@@ sample begin 0:0
// [A]
// クラスTestScoreClientは、
//      * dip_test_score_client.h
//      * dip_test_score_client.cpp
// で宣言・定義され、
// クラスTestScoreLoaderは、
//      * dip_test_score.h(このファイル)
//      * dip_test_score.cpp
// で宣言・定義されされている。
// TestScoreLoaderは宣言・定義の中にTestScoreClientを使用しているため、
//      * dip_test_score.cpp -> dip_test_score_client.h
// の依存関係が発生してる(dip_test_score.h -> dip_test_score_client.hの依存関係は、
// dip_test_score.h内のTestScoreClientの前方宣言で回避)。
// クラスの名前からもわかる通り、
//      * TestScoreClientはTestScoreLoaderのクライアント
//      * TestScoreLoaderはTestScoreClientのサーバ
// であるため、この依存関係
//      * TestScoreLoader -> TestScoreClient(逆の依存関係もあるため、双方向依存)
//      * dip_test_score.cpp -> dip_test_score_client.h
// はDIPに反し、機能拡張(や、場合よっては単体テスト可能なパッケージ構成維持)
// に多大な悪影響がある(TestScoreLoaderを使うTestScoreClient2を新たに定義したときに
// TestScoreLoaderがどのように修正されるかを考えればこの問題に気づくだろう)。
// この問題に対処せよ。

// [解説]
// TestScoreLoaderを「TestScoreClientへの依存」から「TestScoreClientIFへの依存」に変更し、
// TestScoreClientIFをTestScoreLoaderと同じファイル(このファイル)で宣言・定義したことにより、
//      * TestScoreLoader -> TestScoreClient
// の依存関係は解消された。
// TestScoreClientは、TestScoreClientIFを継承することでTestScoreLoaderのサービスを使用できる。
// この依存関係は、
//      * TestScoreClient -> TestScoreClientIF
// であり、クライアントからサーバへの依存であるため問題にならない。

class TestScore {
    // @@@ ignore begin
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
    // @@@ ignore end
};

// @@@ ignore begin
std::string           ToString(TestScore const& ts);
TestScore             LoadCSV(std::string const& filename);
void                  StoreCSV(TestScore const& test_score, std::string const& filename);
TestScore::ScoreOne_t Average(TestScore const& test_score);
// @@@ ignore end

class TestScoreClientIF {
public:
    TestScoreClientIF()          = default;
    virtual ~TestScoreClientIF() = default;
    virtual void Done()          = 0;
};

class TestScoreLoader {
public:
    TestScoreLoader() {}
    ~TestScoreLoader();
    void      LoadCSV_Async(std::string&& filename, TestScoreClientIF& client);
    TestScore LoadCSV_Get() { return future_.get(); }

private:
    std::future<TestScore> future_{};
};
// @@@ sample end
}  // namespace Solid_DIP_A
