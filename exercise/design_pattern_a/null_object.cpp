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
    virtual std::string good_morning() const override { return u8"good morning"; }
    virtual std::string hello() const override { return u8"hello"; }
    virtual std::string good_evening() const override { return u8"good evening"; }
};

class GreetingState_Japanese : public GreetingState {
    virtual std::string good_morning() const override { return u8"おはよう"; }
    virtual std::string hello() const override { return u8"こんにちは"; }
    virtual std::string good_evening() const override { return u8"こんばんは"; }
};

class GreetingState_French : public GreetingState {
    virtual std::string good_morning() const override { return u8"Bonjour"; }
    virtual std::string hello() const override { return u8"Bonjour"; }
    virtual std::string good_evening() const override { return u8"bonne soirée"; }
};

// @@@ sample begin 0:0
// [A]
// 下記クラスPersonにはgreeting_のヌルチェックを行う三項演算子が3つある。
// これはヌルポインタアクセスを起こしやすいアンチパターンであるため、
// Null Objectパターンを用いリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

// [解説]
// * 通常Null Objectパターンは
//      if(object_ptr != nullptr) { ... }
//   のようなコードが頻繁に存在する場合にそのコードの繰り返しを無くすためのものであるが、
//   本例では対象が生のポインタでなくスマートポインタに適用した。
// * 本例では、GoodMorning等が単純であるためGreetingにNVIを適用していないが、NVIを適用しても良い。
// * 本例では、ヌルかどうかの同型条件分岐が3個しかないコードにNull Objectパターンを適用した。
//   例題のためそうしたが、この程度の単純なコードにこのパターンを適用するのはやりすぎである。
//   この程度のコードクローンであれば一つのヘルパー関数にまとめた方が実践的である。

class Greeting {
public:
    explicit Greeting(Language lang = Language::English) : state_{new_state(lang)} {}
    virtual ~Greeting() = default;
    void SetLanguage(Language lang) { state_ = new_state(lang); }

    virtual std::string GoodMorning() const { return state_->GoodMorning(); }
    virtual std::string Hello() const { return state_->Hello(); }
    virtual std::string GoodEvening() const { return state_->GoodEvening(); }

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

class GreetingSilent : public Greeting {
public:
    explicit GreetingSilent()          = default;
    virtual ~GreetingSilent() override = default;

    virtual std::string GoodMorning() const override { return ""; }
    virtual std::string Hello() const override { return ""; }
    virtual std::string GoodEvening() const override { return ""; }
};

class Person {
public:
    explicit Person(Language lang, bool silent = false)
        : greeting_{silent ? std::make_unique<GreetingSilent>() : std::make_unique<Greeting>(lang)}
    {
    }

    std::string GoodMorning() const { return greeting_->GoodMorning(); }
    std::string Hello() const { return greeting_->Hello(); }
    std::string GoodEvening() const { return greeting_->GoodEvening(); }

private:
    std::unique_ptr<Greeting> greeting_;
};

TEST(DesignPatternA, NullObject)
{
    auto e = Person{Language::English};

    ASSERT_EQ(u8"good morning", e.GoodMorning());
    ASSERT_EQ(u8"hello", e.Hello());
    ASSERT_EQ(u8"good evening", e.GoodEvening());

    auto j = Person{Language::Japanese};
    ASSERT_EQ(u8"おはよう", j.GoodMorning());
    ASSERT_EQ(u8"こんにちは", j.Hello());
    ASSERT_EQ(u8"こんばんは", j.GoodEvening());

    auto f = Person{Language::French};
    ASSERT_EQ(u8"Bonjour", f.GoodMorning());
    ASSERT_EQ(u8"Bonjour", f.Hello());
    ASSERT_EQ(u8"bonne soirée", f.GoodEvening());

    auto e_s = Person{Language::English, true};

    ASSERT_EQ(u8"", e_s.GoodMorning());
    ASSERT_EQ(u8"", e_s.Hello());
    ASSERT_EQ(u8"", e_s.GoodEvening());
}
// @@@ sample end
}  // namespace
