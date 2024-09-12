#include "gtest_wrapper.h"

namespace {

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

// @@@ sample begin 0:0
// [Q]
// 下記クラスPersonにはgreeting_のヌルチェックを行う三項演算子が3つある。
// これはヌルポインタアクセスを起こしやすいアンチパターンであるため、
// Null Objectパターンを用いリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

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

class Person {
public:
    explicit Person(Language lang, bool silent = false)
        : greeting_{silent ? std::unique_ptr<Greeting>{} : std::make_unique<Greeting>(lang)}
    {
    }

    std::string GoodMorning() { return greeting_ ? greeting_->GoodMorning() : ""; }
    std::string Hello() { return greeting_ ? greeting_->Hello() : ""; }
    std::string GoodEvening() { return greeting_ ? greeting_->GoodEvening() : ""; }

private:
    std::unique_ptr<Greeting> greeting_;
};

TEST(DesignPatternQ, NullObject)
{
    auto e = Person{Language::English};

    ASSERT_EQ("good morning", e.GoodMorning());
    ASSERT_EQ("hello", e.Hello());
    ASSERT_EQ("good evening", e.GoodEvening());

    auto j = Person{Language::Japanese};
    ASSERT_EQ("おはよう", j.GoodMorning());
    ASSERT_EQ("こんにちは", j.Hello());
    ASSERT_EQ("こんばんは", j.GoodEvening());

    auto f = Person{Language::French};
    ASSERT_EQ("Bonjour", f.GoodMorning());
    ASSERT_EQ("Bonjour", f.Hello());
    ASSERT_EQ("bonne soirée", f.GoodEvening());

    auto e_s = Person{Language::English, true};

    ASSERT_EQ("", e_s.GoodMorning());
    ASSERT_EQ("", e_s.Hello());
    ASSERT_EQ("", e_s.GoodEvening());
}
// @@@ sample end
}  // namespace
