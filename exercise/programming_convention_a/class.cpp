#include <string>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 以下のクラスABCの凝集度が高くなるように、ABC、HasRealNumberSolutionをリファクタリングせよ。
// その時に、他の問題があればそれも併せて修正せよ。

class ABC {  // 2次方程式のパラメータ保持
public:
    explicit ABC(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

    bool HasRealNumberSolution() const noexcept { return 0 <= discriminant(); }

private:
    int32_t const a_;
    int32_t const b_;
    int32_t const c_;

    int32_t discriminant() const noexcept  // 判定式
    {
        return b_ * b_ - 4 * a_ * c_;
    }
};

bool HasRealNumberSolution(ABC const& abc) noexcept { return abc.HasRealNumberSolution(); }

TEST(ProgrammingConventionClassA, Cohision)
{
    {
        auto const abc = ABC{1, 2, 1};

        ASSERT_TRUE(HasRealNumberSolution(abc));
    }
    {
        auto const abc = ABC{2, 0, 1};

        ASSERT_FALSE(HasRealNumberSolution(abc));
    }
}
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 以下のMemberInitのメンバ変数を適切な方法で初期化せよ。

class MemberInit {
public:
    MemberInit() noexcept {}

    explicit MemberInit(int a) noexcept : a_{a}, b_{a, 99} {}

    int32_t GetA() const noexcept { return a_; }

    static constexpr size_t b_len{2};
    int32_t const (&GetB() const noexcept)[b_len] { return b_; }
    int32_t GetC() const noexcept { return c_; }

private:
    int32_t const a_{0};
    int32_t const b_[b_len]{1, 1};
    int32_t const c_{2};
};

TEST(ProgrammingConventionClassA, MemberInit)
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
// [A]
// 以下のクラスBaseはオブジェクトのスライシングを引き起こす。
// このような誤用を起こさないようにするために、Baseオブジェクトのコピーを禁止せよ。
// 合わせてクラスDerivedも含め、不十分な記述を修正せよ。

class Base {
public:
    explicit Base(char const* name = nullptr) noexcept : name_{name == nullptr ? "Base" : name} {}
    virtual ~Base() = default;

    virtual char const* Name0() const noexcept { return "Base"; }
    char const*         Name1() const noexcept { return name_; }

    Base& operator=(Base const& rhs) = delete;
    Base(Base const&)                = delete;

private:
    char const* name_;
};

class Derived final : public Base {
public:
    Derived() noexcept : Base{"Derived"} {}

    virtual char const* Name0() const noexcept override { return "Derived"; }
};

TEST(ProgrammingConventionClassA, Slicing)
{
    auto  b     = Base{};
    auto  d     = Derived{};
    Base& d_ref = d;

    // 以下はBase、Derivedの単純なテスト
    ASSERT_STREQ("Base", b.Name0());
    ASSERT_STREQ("Base", b.Name1());
    ASSERT_STREQ("Derived", d_ref.Name0());
    ASSERT_STREQ("Derived", d_ref.Name1());

#if 0
    // Base::operator=(Base const& rhs)をdeleteしたためにこのような誤用はコンパイルエラーになる。

    // 以下はbがスライスされたオブジェクトであることのテスト
    // こういった誤用を防ぐためにBaseのコピーを禁止せよ。
    b = d_ref;
    ASSERT_STREQ("Base", b.Name0());     // vtblはBaseになるから
    ASSERT_STREQ("Derived", b.Name1());  // name_はコピーされるから
#else
    // 意図的に上記のようなことがしたい場合、下記のようにするべき。
    auto b_copy = Base{d_ref.Name0()};
    ASSERT_STREQ("Base", b_copy.Name0());     // vtblはBaseになるから
    ASSERT_STREQ("Derived", b_copy.Name1());  // name_はコピーされるから
#endif
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

TEST(ProgrammingConventionClassA, Ownership)
{
    // clang-format off
    // [A]
    // 以下の単体テストを完成させよ。

    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない

    auto a0 = std::make_unique<A>(0);           // a0はA(0)を所有
    auto a1 = std::make_unique<A>(1);           // a1はA(1)を所有
    auto x = X {};

    ASSERT_EQ(1,  A::LastConstructedNum());     // A(1)は生成された
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
    ASSERT_EQ(0, a0->GetNum());                 // a0はA(0)を所有
    x.Move(std::move(a0));                      // a0からxへA(0)の所有権の移動
    ASSERT_FALSE(a0);                           // a0は何も所有していない

    ASSERT_EQ(1, a1->GetNum());                 // a1はA(1)を所有
    x.Move(std::move(a1));                      // xによるA(0)の解放
                                                // a1からxへA(1)の所有権の移動
    ASSERT_EQ(0, A::LastDestructedNum());       // A(0)は解放された
    ASSERT_FALSE(a1);                           // a1は何も所有していない
    ASSERT_EQ(1, x.GetA()->GetNum());           // xはA(1)を所有

    std::unique_ptr<A> a2{x.Release()};         // xからa2へA(1)の所有権の移動
    ASSERT_EQ(nullptr, x.GetA());               // xは何も所有していない
    ASSERT_EQ(1, a2->GetNum());                 // a2はA(1)を所有
    {
        std::unique_ptr<A> a3{std::move(a2)};
        ASSERT_FALSE(a2);                       // a2は何も所有していない
        ASSERT_EQ(1, a3->GetNum());             // a3はA(1)を所有
    }                                           // a3によるA(1)の解放
    ASSERT_EQ(1, A::LastDestructedNum());
    // clang-format on
}
// @@@ sample end
}  // namespace
