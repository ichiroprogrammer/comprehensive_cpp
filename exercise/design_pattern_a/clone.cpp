#include <memory>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// TEST(DesignPatternQ, Clone)に記述したように、オブジェクトのスライシングによる影響で、
// Base型ポインタに代入されたDerivedインスタンスへのコピーは部分的にしか行われない。
// Cloneパターンを使用してこの問題を修正せよ。
// また、その他の問題があれば合わせて修正せよ。

class Base {
public:
    explicit Base(std::string name) : name1_{std::move(name)} {}
    virtual ~Base() = default;
    virtual std::string const& GetName() const noexcept { return name1_; }

    virtual std::unique_ptr<Base> Clone() const { return std::make_unique<Base>(name1_); }

    Base(Base const&)            = delete;
    Base& operator=(Base const&) = delete;

private:
    std::string name1_;
};

class Derived final : public Base {
public:
    explicit Derived(std::string name1 = "", std::string name2 = "")
        : Base{std::move(name1)}, name2_{std::move(name2)}
    {
    }
    virtual ~Derived() override = default;
    virtual std::string const& GetName() const noexcept override { return name2_; }

    virtual std::unique_ptr<Base> Clone() const override { return CloneOwn(); }

    std::unique_ptr<Derived> CloneOwn() const
    {
        return std::make_unique<Derived>(Base::GetName(), name2_);
    }

private:
    std::string name2_;
};

TEST(DesignPatternA, Clone)
{
    Derived d1{"name1", "name2"};

    ASSERT_EQ("name1", d1.Base::GetName());
    ASSERT_EQ("name2", d1.GetName());

    std::unique_ptr<Derived> d2 = d1.CloneOwn();
    ASSERT_EQ("name1", d2->Base::GetName());
    ASSERT_EQ("name2", d2->GetName());

    std::unique_ptr<Base> b3 = d1.Clone();  // コピーの代わりにクローン

    ASSERT_EQ("name1", b3->Base::GetName());
    ASSERT_EQ("name2", b3->GetName());  // ちゃんとコピーされた。
}
// @@@ sample end
}  // namespace
