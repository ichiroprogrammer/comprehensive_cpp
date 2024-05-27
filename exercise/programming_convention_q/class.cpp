#include <string>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 以下のクラスABCの凝集度が高くなるように、ABC、HasRealNumberSolutionをリファクタリングせよ。
// その時に、他の問題があればそれも併せて修正せよ。

class ABC {  // 2次方程式のパラメータ保持
public:
    ABC(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

    int32_t GetA() const { return a_; }
    int32_t GetB() const { return b_; }
    int32_t GetC() const { return c_; }
    void    SetA(int32_t a) { a_ = a; }
    void    SetB(int32_t b) { b_ = b; }
    void    SetC(int32_t c) { c_ = c; }

private:
    int32_t a_;
    int32_t b_;
    int32_t c_;
};

bool HasRealNumberSolution(ABC abc)
{
    auto const discriminant = abc.GetB() * abc.GetB() - 4 * abc.GetA() * abc.GetC();  // 判定式

    return 0 <= discriminant;
}

TEST(ProgrammingConventionClassQ, Cohision)
{
    {
        auto abc = ABC{1, 2, 1};

        ASSERT_TRUE(HasRealNumberSolution(abc));
    }
    {
        auto abc = ABC{2, 0, 1};

        ASSERT_FALSE(HasRealNumberSolution(abc));
    }
}
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 以下のMemberInitのメンバ変数を適切な方法で初期化せよ。

class MemberInit {
public:
    MemberInit() noexcept
    {
        a_    = 0;
        b_[0] = 1;
        b_[1] = 1;
        c_    = 2;
    }

    explicit MemberInit(int a) noexcept
    {
        a_    = a;
        b_[0] = a;
        b_[1] = 99;
        c_    = 2;
    }

    int32_t       GetA() noexcept { return a_; }
    int32_t*      GetB() noexcept { return b_; }
    int32_t       GetC() noexcept { return c_; }
    static size_t b_len;

private:
    int32_t a_;
    int32_t b_[2];
    int32_t c_;
};
size_t MemberInit::b_len = 2;

TEST(ProgrammingConventionClassQ, MemberInit)
{
    {
        auto mi = MemberInit{};

        ASSERT_EQ(0, mi.GetA());
        ASSERT_EQ(1, mi.GetB()[0]);
        ASSERT_EQ(1, mi.GetB()[1]);
        ASSERT_EQ(2, mi.GetC());
    }
    {
        auto mi = MemberInit{1};

        ASSERT_EQ(1, mi.GetA());
        ASSERT_EQ(1, mi.GetB()[0]);
        ASSERT_EQ(99, mi.GetB()[1]);
        ASSERT_EQ(2, mi.GetC());
    }
}
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 以下のクラスBaseはオブジェクトのスライシングを引き起こす。
// このような誤用を起こさないようにするために、Baseオブジェクトのコピーを禁止せよ。
// 合わせてクラスDerivedも含め、不十分な記述を修正せよ。

class Base {
public:
    Base(char const* name = nullptr) noexcept : name_{name == nullptr ? "Base" : name} {}
    ~Base() = default;

    virtual char const* Name0() { return "Base"; }
    char const*         Name1() { return name_; }

private:
    char const* name_;
};

class Derived final : public Base {
public:
    Derived() noexcept : Base{"Derived"} {}

    char const* Name0() { return "Derived"; }
};

TEST(ProgrammingConventionClassQ, Slicing)
{
    auto  b     = Base{};
    auto  d     = Derived{};
    Base& d_ref = d;

    // 以下はBase、Derivedの単純なテスト
    ASSERT_STREQ("Base", b.Name0());
    ASSERT_STREQ("Base", b.Name1());
    ASSERT_STREQ("Derived", d_ref.Name0());
    ASSERT_STREQ("Derived", d_ref.Name1());

    // 以下はbがスライスされたオブジェクトであることのテスト
    // こういった誤用を防ぐためにBaseのコピーを禁止せよ。
    b = d_ref;
    ASSERT_STREQ("Base", b.Name0());     // vtblはBaseになるから
    ASSERT_STREQ("Derived", b.Name1());  // name_はコピーされるから
}
// @@@ sample end

// @@@ sample begin 3:0
class A {
public:
    explicit A(int32_t n) noexcept : num_{n} { last_constructed_num_ = num_; }
    ~A() { last_destructed_num_ = num_; }

    int32_t GetNum() const noexcept { return num_; }

    static int32_t LastConstructedNum() noexcept { return last_constructed_num_; }
    static int32_t LastDestructedNum() noexcept { return last_destructed_num_; }

private:
    int32_t        num_;
    static int32_t last_constructed_num_;
    static int32_t last_destructed_num_;
};

int32_t A::last_constructed_num_ = -1;
int32_t A::last_destructed_num_  = -1;

class X final {
public:
    void Move(std::unique_ptr<A>&& ptr) noexcept
    {
        ptr_ = std::move(ptr);  // ptr->ptr_へ所有権の移動
    }

    std::unique_ptr<A> Release() noexcept
    {
        return std::move(ptr_);  // ptr_から外部への所有権の移動
    }

    A const* GetA() const noexcept { return ptr_.get(); }
    X()  = default;
    ~X() = default;

private:
    std::unique_ptr<A> ptr_{};
};

TEST(ProgrammingConventionClassQ, Ownership)
{
    // clang-format off
    // [Q]
    // 以下の単体テストを完成させよ。
    // ?はインスタンスが入り、?????はTRUEかFALSEが入る。

    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない

    auto a0 = std::make_unique<A>(0);           // a0はA(0)を所有
    auto a1 = std::make_unique<A>(1);           // a1はA(1)を所有
    auto x = X {};

//  ASSERT_EQ(?, A::LastConstructedNum());      // A(1)は生成された
//  ASSERT_EQ(?, A::LastDestructedNum());       // まだ、A::~A()は呼ばれてない
//  ASSERT_EQ(?, a0->GetNum());                 // a0はA(0)を所有
    x.Move(std::move(a0));                      // a0からxへA(0)の所有権の移動
//  ASSERT_?????(a0);                           // a0は何も所有していない

//  ASSERT_EQ(?, a1->GetNum());                 // a1はA(1)を所有
    x.Move(std::move(a1));                      // xによるA(0)の解放
                                                // a1からxへA(1)の所有権の移動
//  ASSERT_EQ(?, A::LastDestructedNum());       // A(0)は解放された
//  ASSERT_?????(a1);                           // a1は何も所有していない
//  ASSERT_EQ(?, x.GetA()->GetNum());           // xはA(1)を所有

    std::unique_ptr<A> a2{x.Release()};         // xからa2へA(1)の所有権の移動
//  ASSERT_EQ(?, x.GetA());                     // xは何も所有していない
//  ASSERT_EQ(?, a2->GetNum());                 // a2はA(1)を所有
    {
        std::unique_ptr<A> a3{std::move(a2)};
//      ASSERT_?????(a2);                       // a2は何も所有していない
//      ASSERT_EQ(?, a3->GetNum());             // a3はA(1)を所有
    }                                           // a3によるA(1)の解放
//  ASSERT_EQ(?, A::LastDestructedNum());
    // clang-format on
}
// @@@ sample end
}  // namespace
