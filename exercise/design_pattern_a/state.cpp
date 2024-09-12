#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記クラスGreetingにはlang_に対する同型のswitch文が3個ある。
// これは機能追加時にバグが混入しやすいアンチパターンであるため、
// Stateパターンを用いリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

enum class Language { English, Japanese, French };

class GreetingState {
public:
    virtual ~GreetingState() = default;
    std::string GoodMorning() { return good_morning(); }
    std::string Hello() { return hello(); }
    std::string GoodEvening() { return good_evening(); }

private:
    virtual std::string good_morning() const = 0;
    virtual std::string hello() const        = 0;
    virtual std::string good_evening() const = 0;
};

class GreetingState_English : public GreetingState {
    virtual std::string good_morning() const override { return "good morning"; }
    virtual std::string hello() const override { return "hello"; }
    virtual std::string good_evening() const override { return "good evening"; }
};

class GreetingState_Japanese : public GreetingState {
    virtual std::string good_morning() const override { return "おはよう"; }
    virtual std::string hello() const override { return "こんにちは"; }
    virtual std::string good_evening() const override { return "こんばんは"; }
};

class GreetingState_French : public GreetingState {
    virtual std::string good_morning() const override { return "Bonjour"; }
    virtual std::string hello() const override { return "Bonjour"; }
    virtual std::string good_evening() const override { return "bonne soirée"; }
};

class Greeting {
public:
    explicit Greeting(Language lang = Language::English) : state_{new_state(lang)} {}
    void SetLanguage(Language lang) { state_ = new_state(lang); }

    std::string GoodMorning() const { return state_->GoodMorning(); }
    std::string Hello() const { return state_->Hello(); }
    std::string GoodEvening() const { return state_->GoodEvening(); }

private:
    std::unique_ptr<GreetingState> state_;

    static std::unique_ptr<GreetingState> new_state(Language lang)
    {
        switch (lang) {
        case Language::Japanese:
            return std::make_unique<GreetingState_Japanese>();
        case Language::French:
            return std::make_unique<GreetingState_French>();
        case Language::English:
        default:
            return std::make_unique<GreetingState_English>();
        }
    }
};

TEST(DesignPatternA, State)
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
