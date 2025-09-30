#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスBase、Derivedはクローンパターンをしているが、Clone関数はnewしたオブジェクトであるため、
// メモリーリークを起こしやすい。std::unique_ptrを使用してこの問題に対処せよ。

class Base {
public:
    explicit Base(std::string name) : name1_{std::move(name)} {}
    virtual ~Base() = default;
    virtual std::string const& GetName() const noexcept { return name1_; }

    virtual Base* Clone() const { return new Base(name1_); }

    Base(Base const&)            = delete;
    Base& operator=(Base const&) = delete;

private:
    std::string name1_;
};

class Derived final : public Base {
public:
    explicit Derived(std::string name1 = "", std::string name2 = "") : Base{std::move(name1)}, name2_{std::move(name2)}
    {
    }
    virtual ~Derived() override = default;
    virtual std::string const& GetName() const noexcept override { return name2_; }

    virtual Derived* Clone() const override { return new Derived{Base::GetName(), name2_}; }

private:
    std::string name2_;
};

TEST(DesignPatternQ, RAII)
{
    Derived  d1{"name1", "name2"};
    Derived* d2{d1.Clone()};

    ASSERT_EQ("name1", d2->Base::GetName());
    ASSERT_EQ("name2", d2->GetName());

    delete d2;

    Base* b3 = d1.Clone();

    ASSERT_EQ("name1", b3->Base::GetName());
    ASSERT_EQ("name2", b3->GetName());

    delete b3;
}
// @@@ sample end
}  // namespace
