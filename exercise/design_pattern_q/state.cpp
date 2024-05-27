#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスGreetingにはlang_に対する同型のswitch文が3個ある。
// これは機能追加時にバグが混入しやすいアンチパターンであるため、
// Stateパターンを用いリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

enum class Language { English, Japanese, French };

class Greeting {
public:
    explicit Greeting(Language lang = Language::English) noexcept : lang_{lang} {}
    void SetLanguage(Language lang) noexcept { lang_ = lang; }

    std::string GoodMorning()
    {
        switch (lang_) {
        case Language::Japanese:
            return u8"おはよう";
        case Language::French:
            return u8"Bonjour";
        case Language::English:
        default:
            return u8"good morning";
        }
    }

    std::string Hello()
    {
        switch (lang_) {
        case Language::Japanese:
            return u8"こんにちは";
        case Language::French:
            return u8"Bonjour";
        case Language::English:
        default:
            return u8"hello";
        }
    }

    std::string GoodEvening()
    {
        switch (lang_) {
        case Language::Japanese:
            return u8"こんばんは";
        case Language::French:
            return u8"bonne soirée";
        case Language::English:
        default:
            return u8"good evening";
        }
    }

private:
    Language lang_;
};

TEST(DesignPatternQ, State)
{
    auto greeting = Greeting{};

    ASSERT_EQ(u8"good morning", greeting.GoodMorning());
    ASSERT_EQ(u8"hello", greeting.Hello());
    ASSERT_EQ(u8"good evening", greeting.GoodEvening());

    greeting.SetLanguage(Language::Japanese);
    ASSERT_EQ(u8"おはよう", greeting.GoodMorning());
    ASSERT_EQ(u8"こんにちは", greeting.Hello());
    ASSERT_EQ(u8"こんばんは", greeting.GoodEvening());

    greeting.SetLanguage(Language::French);
    ASSERT_EQ(u8"Bonjour", greeting.GoodMorning());
    ASSERT_EQ(u8"Bonjour", greeting.Hello());
    ASSERT_EQ(u8"bonne soirée", greeting.GoodEvening());

    greeting.SetLanguage(Language::English);
    ASSERT_EQ(u8"good morning", greeting.GoodMorning());
    ASSERT_EQ(u8"hello", greeting.Hello());
    ASSERT_EQ(u8"good evening", greeting.GoodEvening());
}
// @@@ sample end
}  // namespace
