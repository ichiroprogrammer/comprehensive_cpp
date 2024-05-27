#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// TEST(DesignPatternQ, Clone)に記述したように、オブジェクトのスライシングによる影響で、
// Base型ポインタに代入されたDerivedインスタンスへのコピーは部分的にしか行われない。
// Cloneパターンを使用してこの問題を修正せよ。
// また、その他の問題があれば合わせて修正せよ。

class Base {
public:
    explicit Base(std::string name) : name1_{name} {}
    virtual ~Base() = default;
    virtual std::string const& GetName() { return name1_; }

private:
    std::string name1_;
};

class Derived final : public Base {
public:
    explicit Derived(std::string name1 = "", std::string name2 = "") : Base{name1}, name2_{name2} {}
    virtual ~Derived() = default;
    virtual std::string const& GetName() { return name2_; }

private:
    std::string name2_;
};

TEST(DesignPatternQ, Clone)
{
    Derived d1{"name1", "name2"};

    ASSERT_EQ("name1", d1.Base::GetName());
    ASSERT_EQ("name2", d1.GetName());

    Derived d2{d1};
    ASSERT_EQ("name1", d2.Base::GetName());
    ASSERT_EQ("name2", d2.GetName());

    Derived d3;
    Base*   b3 = &d3;

    *b3 = d1;  // d1からd3へコピーしたつもりだが、スライスによりうまく行かない。

    ASSERT_EQ("name1", b3->Base::GetName());
#if 0
    ASSERT_EQ("name2", b3->GetName());   // スライスの影響でname2_がコピーされていない。
#else
    ASSERT_EQ("", d3.GetName());
#endif
}
// @@@ sample end
}  // namespace
