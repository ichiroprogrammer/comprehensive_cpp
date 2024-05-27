#include <typeinfo>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスBase、Derived、DerivedDerivedの前処理はクローンコードになっている。
// NVIを用いて、この問題に対処せよ。

class Base {
public:
    explicit Base(std::string name) : name1_{name} {}
    virtual ~Base() = default;
    std::string const& GetName1() const noexcept { return name1_; }

    virtual bool IsEqual(Base const& rhs) const noexcept
    {
        if (this == &rhs) {
            return true;
        }

        if (typeid(*this) != typeid(rhs)) {
            return false;
        }

        return name1_ == rhs.name1_;
    }

private:
    std::string name1_;
};

class Derived : public Base {
public:
    explicit Derived(std::string name1 = "", std::string name2 = "") : Base{name1}, name2_{name2} {}
    virtual ~Derived() override = default;
    std::string const& GetName2() const noexcept { return name2_; }

    virtual bool IsEqual(Base const& rhs) const noexcept override
    {
        if (this == &rhs) {
            return true;
        }

        if (!Base::IsEqual(rhs)) {
            return false;
        }

        auto rhs_d = dynamic_cast<Derived const*>(&rhs);

        return (rhs_d != nullptr) && (name2_ == rhs_d->name2_);
    }

private:
    std::string name2_;
};

class DerivedDerived : public Derived {
public:
    explicit DerivedDerived(std::string name1 = "", std::string name2 = "", std::string name3 = "")
        : Derived{name1, name2}, name3_{name3}
    {
    }
    virtual ~DerivedDerived() override = default;
    std::string const& GetName3() const noexcept { return name3_; }

    virtual bool IsEqual(Base const& rhs) const noexcept override
    {
        if (this == &rhs) {
            return true;
        }

        if (!Derived::IsEqual(rhs)) {
            return false;
        }

        auto rhs_d = dynamic_cast<DerivedDerived const*>(&rhs);

        return (rhs_d != nullptr) && (name3_ == rhs_d->name3_);
    }

private:
    std::string name3_;
};

TEST(DesignPatternQ, NVI)
{
    auto b1 = Base{"b1"};

    ASSERT_TRUE(b1.IsEqual(Base{b1}));
    ASSERT_TRUE(b1.IsEqual(Base{"b1"}));
    ASSERT_FALSE(b1.IsEqual(Base{"b2"}));
    ASSERT_FALSE(b1.IsEqual(Derived{"b1", "d1"}));

    auto d1 = Derived{"b1", "d1"};

    ASSERT_FALSE(d1.IsEqual(Base{"b1"}));
    ASSERT_TRUE(d1.IsEqual(d1));
    ASSERT_TRUE(d1.IsEqual(Derived{"b1", "d1"}));
    ASSERT_FALSE(d1.IsEqual(Derived{"b1", "d2"}));
    ASSERT_FALSE(d1.IsEqual(DerivedDerived{"b1", "d1", "dd2"}));

    auto dd1 = DerivedDerived{"b1", "d1", "dd1"};

    ASSERT_FALSE(dd1.IsEqual(Base{"b1"}));
    ASSERT_FALSE(dd1.IsEqual(Derived{"b1", "d1"}));
    ASSERT_TRUE(dd1.IsEqual(dd1));
    ASSERT_TRUE(dd1.IsEqual(DerivedDerived{"b1", "d1", "dd1"}));
    ASSERT_FALSE(dd1.IsEqual(DerivedDerived{"b1", "d1", "dd2"}));
}
// @@@ sample end
}  // namespace
