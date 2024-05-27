#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記AppConfigはアプリケーション全体の設定を管理するためのクラスである。
// 目的上、そのインスタンスAppConfigは広域のアクセスが必要であり、
// グローバルインスタンスとして実装している。
// グローバルインスタンスは、初期化の順番が標準化されておらず、
// 多くの処理系ではリンクの順番に依存しているため、
// アプリケーション立ち上げ時に様々な問題を起こすことがある。
// こういった問題を回避するため、AppConfigをSingleton化せよ。
// また他の問題があれば合わせて修正せよ。

// [解説]
// * AppConfigをSingletonにした。
//      * インスタンスを返すInst()と同じインスタンスをconst修飾したものを返すInstConst()を追加。
//      * コンストラクタをprivateにした。
//      * copyコンストラクタを= deleteした(こうすればmoveコンストラクタも= deleteされる)。
// * リファクタリング
//      * BaseColorをスコープドenumにした。
//      * GetXxxをconst関数にした。
//      * GetUserNameの戻りをconstリファレンスにした。
//      * コピー演算子を使用しSetDefaultをシンプルにした。

class AppConfig {
public:
    static AppConfig& Inst()
    {
        static auto inst = AppConfig{};

        return inst;
    }

    static AppConfig const& InstConst() { return Inst(); }

    enum class BaseColor { Red, Green, Black };

    void      SetBaseColor(BaseColor color) noexcept { color_ = color; }
    BaseColor GetBaseColor() const noexcept { return color_; }

    void               SetUserName(std::string_view username) { username_ = username; }
    std::string const& GetUserName() const noexcept { return username_; }

    void Logging(bool is_logging) noexcept { is_logging_ = is_logging; }
    bool IsLoggin() const noexcept { return is_logging_; }

    // 他の設定値は省略

    void SetDefault() { *this = AppConfig{}; }

    // これがないとcopyコンストラクタやmoveコンストラクタで別のインスタンスが作れる。
    //    AppConfig app{AppConfig::Inst()};
    //    AppConfig app{std::move(AppConfig::Inst())};
    AppConfig(AppConfig const&) = delete;

private:
    BaseColor   color_{BaseColor::Red};
    std::string username_{"No Name"};
    bool        is_logging_{false};

    AppConfig()                            = default;
    AppConfig& operator=(AppConfig const&) = default;
};

class DesignPatternA_F : public ::testing::Test {
protected:
    virtual void SetUp() override { AppConfig::Inst().SetDefault(); }

    virtual void TearDown() override { AppConfig::Inst().SetDefault(); }
};

TEST_F(DesignPatternA_F, Singleton)
{
    ASSERT_EQ(AppConfig::BaseColor::Red, AppConfig::InstConst().GetBaseColor());
    ASSERT_EQ("No Name", AppConfig::InstConst().GetUserName());
    ASSERT_FALSE(AppConfig::InstConst().IsLoggin());

    AppConfig::Inst().SetBaseColor(AppConfig::BaseColor::Green);
    ASSERT_EQ(AppConfig::BaseColor::Green, AppConfig::InstConst().GetBaseColor());

    AppConfig::Inst().SetUserName("Stroustrup");
    ASSERT_EQ("Stroustrup", AppConfig::InstConst().GetUserName());

    AppConfig::Inst().Logging(true);
    ASSERT_TRUE(AppConfig::InstConst().IsLoggin());

    AppConfig::Inst().SetDefault();
    ASSERT_EQ(AppConfig::BaseColor::Red, AppConfig::InstConst().GetBaseColor());
    ASSERT_EQ("No Name", AppConfig::InstConst().GetUserName());
    ASSERT_FALSE(AppConfig::InstConst().IsLoggin());
}
// @@@ sample end
}  // namespace
