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
            return "おはよう";
        case Language::French:
            return "Bonjour";
        case Language::English:
        default:
            return "good morning";
        }
    }

    std::string Hello()
    {
        switch (lang_) {
        case Language::Japanese:
            return "こんにちは";
        case Language::French:
            return "Bonjour";
        case Language::English:
        default:
            return "hello";
        }
    }

    std::string GoodEvening()
    {
        switch (lang_) {
        case Language::Japanese:
            return "こんばんは";
        case Language::French:
            return "bonne soirée";
        case Language::English:
        default:
            return "good evening";
        }
    }

private:
    Language lang_;
};

TEST(DesignPatternQ, State)
{
    auto greeting = Greeting{};

    ASSERT_EQ("good morning", greeting.GoodMorning());
    ASSERT_EQ("hello", greeting.Hello());
    ASSERT_EQ("good evening", greeting.GoodEvening());

    greeting.SetLanguage(Language::Japanese);
    ASSERT_EQ("おはよう", greeting.GoodMorning());
    ASSERT_EQ("こんにちは", greeting.Hello());
    ASSERT_EQ("こんばんは", greeting.GoodEvening());

    greeting.SetLanguage(Language::French);
    ASSERT_EQ("Bonjour", greeting.GoodMorning());
    ASSERT_EQ("Bonjour", greeting.Hello());
    ASSERT_EQ("bonne soirée", greeting.GoodEvening());

    greeting.SetLanguage(Language::English);
    ASSERT_EQ("good morning", greeting.GoodMorning());
    ASSERT_EQ("hello", greeting.Hello());
    ASSERT_EQ("good evening", greeting.GoodEvening());
}
// @@@ sample end
}  // namespace
