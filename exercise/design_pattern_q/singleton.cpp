#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記AppConfigはアプリケーション全体の設定を管理するためのクラスである。
// 目的上、そのインスタンスAppConfigは広域のアクセスが必要であり、
// グローバルインスタンスとして実装している。
// グローバルインスタンスは、初期化の順番が標準化されておらず、
// 多くの処理系ではリンクの順番に依存しているため、
// アプリケーション立ち上げ時に様々な問題を起こすことがある。
// こういった問題を回避するため、AppConfigをSingleton化せよ。
// また他の問題があれば合わせて修正せよ。

class AppConfig {
public:
    enum BaseColor { Red, Green, Black };

    void      SetBaseColor(BaseColor color) noexcept { color_ = color; }
    BaseColor GetBaseColor() { return color_; }

    void         SetUserName(std::string_view username) { username_ = username; }
    std::string& GetUserName() { return username_; }

    void Logging(bool is_logging) { is_logging_ = is_logging; }
    bool IsLoggin() { return is_logging_; }

    // 他の設定値は省略

    void SetDefault()
    {
        SetBaseColor(Red);
        SetUserName("No Name");
        Logging(false);
    }

private:
    BaseColor   color_{Red};
    std::string username_{"No Name"};
    bool        is_logging_{false};
};

AppConfig AppConfig;

class DesignPatternQ_F : public ::testing::Test {
protected:
    virtual void SetUp() override { AppConfig.SetDefault(); }

    virtual void TearDown() override { AppConfig.SetDefault(); }
};

TEST_F(DesignPatternQ_F, Singleton)
{
    ASSERT_EQ(AppConfig::Red, AppConfig.GetBaseColor());
    ASSERT_EQ("No Name", AppConfig.GetUserName());
    ASSERT_FALSE(AppConfig.IsLoggin());

    AppConfig.SetBaseColor(AppConfig::Green);
    ASSERT_EQ(AppConfig::Green, AppConfig.GetBaseColor());

    AppConfig.SetUserName("Stroustrup");
    ASSERT_EQ("Stroustrup", AppConfig.GetUserName());

    AppConfig.Logging(true);
    ASSERT_TRUE(AppConfig.IsLoggin());

    AppConfig.SetDefault();
    ASSERT_EQ(AppConfig::Red, AppConfig.GetBaseColor());
    ASSERT_EQ("No Name", AppConfig.GetUserName());
    ASSERT_FALSE(AppConfig.IsLoggin());
}
// @@@ sample end
}  // namespace
