#include <iostream>
#include <memory>
#include <mutex>
#include <string>

#include "gtest_wrapper.h"

#include "class.h"
#include "suppress_warning.h"

namespace AccessLevelSample {
// @@@ sample begin 0:0

class A {
    void f0();  // NG デフォルト private を使用しない。
public:
    void f1();  // OK
private:
    void f2();  // OK
protected:
    void f3();  // NG privateの前に定義すべき。
};
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_GCC_NOT_EFF_CPP;

// @@@ sample begin 0:1

class B {
public:
    // @@@ ignore begin
    B() noexcept {}

    ~B() {}
    // @@@ ignore end

    void* f0() noexcept  // NG メンバ変数が保持するポインタを返している
    {
        return v_ptr_;
    }

    std::string* f1() noexcept  // NG メンバ変数へのポインタを返している
    {
        return &str_;
    }

    std::string& f2() noexcept  // NG メンバ変数へのリファレンスを返している
    {
        return str_;
    }

    std::string f3() const noexcept  // OK ただし、パフォーマンスに注意
    {
        return str_;
    }

    std::string const& f4() const noexcept  // OK
    {
        return str_;
    }

private:
    void*       v_ptr_ = nullptr;
    std::string str_{};
};
// @@@ sample end
// @@@ sample begin 0:2

class Integer {
public:
    Integer(int32_t integer) noexcept : integer_{integer} {}

    // メンバ関数に見えるが、非メンバ関数
    friend bool operator==(Integer lhs, Integer rhs) noexcept  // OK
    {
        return lhs.integer_ == rhs.integer_;
    }

private:
    int32_t const integer_;
};

bool operator!=(Integer lhs, Integer rhs) noexcept { return !(lhs == rhs); }
// @@@ sample end
// @@@ sample begin 0:3

class Widget {
public:
    virtual int32_t DoSomething() noexcept  // NG virtualでpublic
    {
        // @@@ ignore begin
        return i_;
        // @@@ ignore end
    }

    int32_t DoSomething(bool b) noexcept  // OK non-virtualでpublic
    {
        return do_something(b);
    }
    // @@@ ignore begin

    Widget() noexcept {}

    virtual ~Widget() {}

    // @@@ ignore end
private:
    virtual int32_t do_something(bool b) noexcept  // OK virtualでprivate
    {
        // @@@ ignore begin
        return b ? 0 : i_;
        // @@@ ignore end
    }
    // @@@ ignore begin

    int32_t i_{0};
    // @@@ ignore end
};
// @@@ sample end
}  // namespace AccessLevelSample

namespace DerivedSample {
// @@@ sample begin 1:0

// private継承。非推奨
class StringWrapper0 final : private std::string {
public:
    explicit StringWrapper0(char const* str) : std::string{str} {}

    void AddStr(char const* str) { *this += str; }

    using std::string::c_str;
};

// 移譲。こちらを優先する
class StringWrapper1 final {
public:
    explicit StringWrapper1(char const* str) : str_{str} {}

    void AddStr(char const* str) { str_ += str; }

    char const* c_str() const noexcept { return str_.c_str(); }

private:
    std::string str_;
};
// @@@ sample end
// @@@ sample begin 1:1

class A {  // デストラクタの呼び出しチェック用のクラス
public:
    A(bool& destructed) noexcept : destructed_{destructed} { destructed_ = false; }
    ~A() { destructed_ = true; }

private:
    bool& destructed_;
};

class BaseNG {  // NG デストラクタが非virtual
public:
    BaseNG() = default;
};

class DerivedNG : public BaseNG {
public:
    DerivedNG(bool& destructed) : a_{std::make_unique<A>(destructed)} {}

private:
    std::unique_ptr<A> a_;
};
// @@@ sample end

namespace {
#ifdef SANITIZER  // sanitizerは下記のメモリリークをレポートするため
#define derived_non_virtual_destructor_Opt DISABLED_derived_non_virtual_destructor
#else
#define derived_non_virtual_destructor_Opt derived_non_virtual_destructor
#endif

TEST(ProgrammingConvention, derived_non_virtual_destructor_Opt)
{
    // @@@ sample begin 1:2

    auto a_destructed = false;
    {
        std::unique_ptr<DerivedNG> d{std::make_unique<DerivedNG>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ないが、、、

    {
        std::unique_ptr<BaseNG> d{std::make_unique<DerivedNG>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_FALSE(a_destructed);  // NG A::~A()が呼ばれないため、メモリリークする
    // @@@ sample end
}
}  // namespace

// @@@ sample begin 1:3

class BaseOK {  // OK デストラクタがvirtual
public:
    BaseOK()          = default;
    virtual ~BaseOK() = default;
};

class DerivedOK : public BaseOK {
public:
    DerivedOK(bool& destructed) : a_{std::make_unique<A>(destructed)} {}

private:
    std::unique_ptr<A> a_;
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, derived_virtual_destructor)
{
    // @@@ sample begin 1:4

    auto a_destructed = false;
    {
        std::unique_ptr<DerivedOK> d{std::make_unique<DerivedOK>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ない

    {
        std::unique_ptr<BaseOK> d{std::make_unique<DerivedOK>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ない
    // @@@ sample end
}
}  // namespace
}  // namespace DerivedSample

SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;

namespace NotStaticMemberVarInitializationSample {
SUPPRESS_WARN_GCC_REORDER;
SUPPRESS_WARN_CLANG_REORDER_CTOR;
class A_OK {
public:
    A_OK(int32_t x, int32_t y) noexcept : a_{x}, b_{x + y}, c_{x}  // OK
    {
    }

private:
    int32_t a_;
    int32_t b_;
    int32_t c_;
};
// @@@ sample end
// @@@ sample begin 2:0

class A1 {
public:
    A1() noexcept {}  // OK NSDMIに統一

private:
    int32_t const a_{1};  // OK NSDMIによる初期化。
                          //    ただし、static constexprにすべき。
    int32_t b_[2]{0, 1};  // OK NSDMIによる初期化
    int32_t c_{5};        // OK NSDMIによる初期化
};

class A2 {
public:
    explicit A2(int a) noexcept   // OK 初期化子リストに統一
        : a_{a}, b_{0, 1}, c_{5}  // OK 初期化子リストによる初期化
    {
    }

private:
    int32_t const a_;
    int32_t       b_[2];
    int32_t       c_;
};

class A3 {
public:
    explicit A3(int a) noexcept : a_{a}  // NG 初期化方法の混在
    {
        c_ = 5;  // NG NSDMIか初期化子リストを使用するべき
    }

private:
    int32_t const a_;
    int32_t       b_[2]{0, 1};  // NG 初期化方法の混在
    int32_t       c_;
};
// @@@ sample end

// @@@ sample begin 2:1

class A4 {
public:
    A4() noexcept {}  // OK

    A4(int32_t e) noexcept : e_{e} {}  // OK 初期化子リストによるe_の上書き
    // 注) A4()とA4(int32_t)はデフォルト引数を使用すれば統一できるが、
    // 例の単純化のためにあえてそれぞれを定義している。

private:
    int32_t d_{5};  // OK NSDMIによる初期化
    int32_t e_{0};  // OK NSDMIによる初期化
};
// @@@ sample end

}  // namespace NotStaticMemberVarInitializationSample

namespace StaticMemberVarInitializationSample {

// @@@ sample begin 3:0
//
uint32_t StaticConstexprVar::MultiplyBy2(uint32_t a) noexcept { return static_constexpr_var_2 * a; }

namespace {
constexpr uint32_t static_constexpr_var_4{4};  // OK クラス内で定義する必要なし
}

uint32_t StaticConstexprVar::MultiplyBy4(uint32_t a) noexcept { return static_constexpr_var_4 * a; }
// @@@ sample end
}  // namespace StaticMemberVarInitializationSample

namespace MutableMemberSample {

// @@@ sample begin 4:0

class A {
public:
    A() = default;

    uint32_t GetValue() const  // OK GetValue()をconstにするためにmutex_はmutable
    {
        auto lock = std::lock_guard{mutex_};  // constでない関数std::mutex::lock()の呼び出し

        return v_;
    }

    void AddValue(uint32_t v) noexcept
    {
        auto lock = std::lock_guard{mutex_};

        v_ += v;
    }

private:
    mutable std::mutex mutex_;  // OK
    uint32_t           v_{0};
};
// @@@ sample end
}  // namespace MutableMemberSample

namespace ObjectLifetimeSample {

class B {
public:
    B() noexcept {}
    uint32_t GetB() const noexcept { return b_; }

private:
    uint32_t b_{3};
};

class A {
public:
    A() noexcept = default;
    explicit A(B const& b) noexcept : a_{b.GetB()} {}

    uint32_t GetA() const noexcept { return a_; }

    void SetB(B* b) noexcept { b_ = b; }

    void DoSomething() noexcept {}

private:
    uint32_t a_{8};
    B*       b_ = nullptr;
};

// @@@ sample begin 5:0

// 初期化前にオブジェクトにアクセスしてしまう例
B& getB() noexcept;

// bが初期される前に(ライフタイム開始前)に、a.A::A()が呼び出される。
// a.A::A()が呼び出される前に、getB()が呼び出される。
// 従って、bが初期化される前にgetB()が未初期化のbのリファレンスを返してしまう。
A a{getB()};

B  b;
B& getB() noexcept { return b; }
// @@@ sample end

void f() noexcept
{
    // @@@ sample begin 5:1

    // ライフタイムが終了したオブジェクトにアクセスしてしまう例
    auto a = A{};
    {
        auto b = B{};
        a.SetB(&b);  // NG aのメンバ変数へ&bを代入。
    }                //    この行でbのライフタイム終了。

    a.DoSomething();  // NG bのポインタを使用して何かすると不定動作。
    // @@@ sample end
}

class E {
public:
    E() noexcept : a_{nullptr} {}

    explicit E(char const* a) : a_{a} {}

private:
    char const* a_;
};

void f0(E&) noexcept {}

void f1(E const&) noexcept {}

void f2(E&&) noexcept {}

SUPPRESS_WARN_UNUSED_VAR;

void h() noexcept
{
    // @@@ sample begin 5:2

    void f0(E&) noexcept;
    void f1(E const&) noexcept;
    void f2(E &&) noexcept;

    // f0(E{});  NG ほとんどのコンパイラではエラー
    f1(E{});  // OK rvalueはconstリファレンスにバインド可
    f2(E{});  // OK rvalueはrvalueリファレンス

    E const& e0 = E{"4"};  // NG rvalueを引数以外のconstリファレンスに代入
    E&&      e1 = E{"5"};  // NG rvalueを引数以外のrvalueリファレンスに代入
    // @@@ sample end
}
}  // namespace ObjectLifetimeSample
SUPPRESS_WARN_END;

namespace {
// @@@ sample begin 6:0

/// @brief クラスのひな形。クラスを定義、宣言するときには、このクラスの下記6関数を適切に
///        定義、宣言すること。
class ClassStationery final {
public:
    ClassStationery()  = delete;
    ~ClassStationery() = delete;

    ClassStationery(ClassStationery const&)                = delete;
    ClassStationery& operator=(ClassStationery const&)     = delete;
    ClassStationery(ClassStationery&&) noexcept            = delete;
    ClassStationery& operator=(ClassStationery&&) noexcept = delete;
};
// @@@ sample end
}  // namespace
