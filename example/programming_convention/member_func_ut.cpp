#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <concepts>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace MemberFuncSample {
// @@@ sample begin 0:0

class A {
public:
    A() : s_ptr_{std::make_unique<std::string>("haha")}, s_inst_{"hihi"} {}

    std::string const& GetString() const noexcept  // OK 必ずconst
    {
        return s_inst_;
    }

    // SetPtrと、SetInstは実質的には同じことを行っている。
    // SetInstはconstと宣言できない(コンパイルエラー)。
    // 従ってSetPtrもconstと宣言してはならない。
    // なお、この問題はstd::experimental::propagate_constを使用することで解決できるが、
    // 名前空間からわかるように、このライブラリが将来にわたって有効かどうかは不明である。
    void SetPtr(std::string_view name) const  // NG このconstはつけてはならない。
    {
        *s_ptr_ = name;
    }

    void SetInst(std::string_view name)  // OK
    {
        s_inst_ = name;
    }

private:
    std::unique_ptr<std::string> s_ptr_;
    std::string                  s_inst_;
};

void f()
{
    A const a;

    a.SetPtr("0");  // constオブジェクトaを変更できてしまう。
    // clang-format off
//  a.SetInst("1"); // constオブジェクトaを変更しようとしたため、
                    // 正しく(constの目的通り)コンパイルエラー。
    // clang-format on
}
// @@@ sample end

// @@@ sample begin 0:1

class B {
public:
    B() noexcept {}

    // GetStringsは、避けがたい理由で、strings_のリファレンスを返さざるを得ないとする。
    // この場合、GetStringsはconstにしてはならない。
    std::vector<std::string>& GetStrings() noexcept { return strings_; }

private:
    std::vector<std::string> strings_{};
};
// @@@ sample end
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_VAR;
SUPPRESS_WARN_CLANG_DANGLING_GSL;
#if !defined(__clang_analyzer__)  // ドキュメントの都合上、scan-buildで指摘されたくない
void g()
{
    // @@@ sample begin 0:2

    char const* s = std::string{"hehe"}.c_str();  // std::string{"hehe"}はrvalue

    std::cout << s << std::endl;  // この時点ではsは解放されている。
    // @@@ sample end
}
#endif
SUPPRESS_WARN_END;
}  // namespace MemberFuncSample

namespace ConstractorSample {

// @@@ sample begin 1:0

class Base {
public:
    Base(std::ostream& os) : os_{os} { os_ << Name() << "::" << __func__ << " -> "; }

    virtual ~Base() { os_ << Name() << "::" << __func__; }

    virtual std::string_view Name() const { return "Base"; }

protected:
    std::ostream& os_;  // protectedなメンバ変数を定義すべきではないが、コードの動作例示のため
};

class Derived : public Base {
public:
    Derived(std::ostream& os) : Base{os} { os_ << Name() << "::" << __func__ << " -> "; }

    virtual ~Derived() { os_ << Name() << "::" << __func__ << " -> "; }

    virtual std::string_view Name() const override { return "Derived"; }
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, call_virtual_in_constructor)
{
    // @@@ sample begin 1:1

    auto oss = std::ostringstream{};

    {
        auto d = Derived{oss};
    }

    ASSERT_EQ("Base::Base -> Derived::Derived -> Derived::~Derived -> Base::~Base", oss.str());
    // つまり、
    // * Base::Base()でのName()の呼び出しは、Derived::Name()ではなくBase::Name()が呼ばれる。
    // * Base::~Base()でのName()の呼び出しは、Derived::Name()ではなくDerived::Name()が呼ばれる。
    // * Derived::~Derived()でのName()の呼び出しは、Derived::Name()ではなくDerived::Name()が呼ばれる。
    // * Base::~Base()でのName()の呼び出しは、Derived::Name()ではなくBase::Name()が呼ばれる。
    // @@@ sample end
}
}  // namespace
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_PARAM;
SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;

// @@@ sample begin 1:2

class A0 {
public:
    // NG int32_tからA0への暗黙の型変換が起こる。
    A0(int32_t a) noexcept : a_{a} {}
    // @@@ ignore begin
private:
    int32_t a_;
    // @@@ ignore end
};

class A1 {
public:
    // OK int32_tからA1への暗黙の型変換をさせない。
    explicit A1(int32_t a) noexcept : a_{a} {}
    // @@@ ignore begin
private:
    int32_t a_;
    // @@@ ignore end
};

class A2 {
public:
    // NG 代入演算子でのリスト初期化ができてしまう。
    A2(int32_t a, int32_t* b) noexcept : a_{a}, b_{b} {}
    // @@@ ignore begin
private:
    int32_t  a_;
    int32_t* b_;
    // @@@ ignore end
};

class A3 {
public:
    // OK 代入演算子でのリスト初期化をさせない。
    explicit A3(int32_t a, int32_t* b) noexcept : a_{a}, b_{b} {}
    // @@@ ignore begin
private:
    int32_t  a_;
    int32_t* b_;
    // @@@ ignore end
};

void f_A0(A0) noexcept {}
void f_A1(A1) noexcept {}
void f_A2(A2) noexcept {}
void f_A3(A3) noexcept {}
// @@@ sample end

TEST(ProgrammingConvention, func_constructor)
{
    // clang-format off
    // @@@ sample begin 1:3

    A0 a0 = 1;           // NG 1からA0への暗黙の型変換。
                         //    このような変換はセマンティクス的不整合につながる場合がある
    // A1 a1 = 1;        // OK explicitの効果で、意図通りコンパイルエラー

    f_A0(1);             // NG 1からA0への暗黙の型変換のためf_A0が呼び出せてしまう
    // f_A1(1);          // OK explicitの効果で、意図通り以下のようなコンパイルエラー
                         //    error: could not convert ‘1’ from ‘int’ to ‘A1’
    f_A1(A1{1});         // OK f_A1の呼び出し

    auto i = 3;
    A2  a2 = {i, &i};    // NG 代入演算子でのリスト初期化をしている

    // A3 a3 = { i, &i };// OK explicitの効果で、意図通りコンパイルエラー
    A3 a3{i, &i};        // OK リスト初期化
    auto a4 = A3{i, &i}; // OK AAA

    f_A2({i, &i});       // NG { i, &i }からA2への暗黙の型変換のためf_A2が呼び出せてしまう
    // f_A3({i, &i});    // OK explicitの効果で、意図通り以下のようなコンパイルエラー
                         //    error: converting to A3 from initializer list would use explicit 
                         //           constructor A3::A3(int32_t, int32_t*)’
    f_A3(A3{i, &i});     // OK f_A3の呼び出し
    // @@@ sample end

    // clang-format on

    IGNORE_UNUSED_VAR(a0, a2, a3, a4);
}
}  // namespace ConstractorSample
namespace AssignmentOperator {
namespace NG {

// @@@ sample begin 2:0

class Widget {
public:
    Widget& operator=(Widget const& rhs)  // NG lvalue修飾無し
    {
        // 何らかの処理
        x_ = rhs.x_;  // @@@ delete
        return *this;
    }

    Widget& operator=(Widget&& rhs) noexcept  // NG lvalue修飾無し
    {
        // 何らかの処理
        x_ = rhs.x_;  // @@@ delete
        return *this;
    }
    // @@@ ignore begin
    explicit Widget(uint32_t x) : x_{x} {}
    uint32_t GetX() const noexcept { return x_; }

private:
    uint32_t x_{0};
    // @@@ ignore end
};
// @@@ sample end

TEST(ProgrammingConvention, func_constructor)
{
    // @@@ sample begin 2:1

    Widget w0{1};
    Widget w1{2};

    w0 = w1;         // これには問題ない
    w1 = Widget{3};  // これにも問題ない

    Widget{2} = w0;         // NG lvalue修飾無しのcopy代入演算子であるため、コンパイルできる
    Widget{3} = Widget{4};  // NG lvalue修飾無しのmove代入演算子であるため、コンパイルできる
    // @@@ sample end

    ASSERT_EQ(2, w0.GetX());
    ASSERT_EQ(3, w1.GetX());
}
}  // namespace NG

namespace OK {

// @@@ sample begin 2:2

class Widget {  // 上記の修正
public:
    Widget& operator=(Widget const& rhs) &  // OK lvalue修飾
    {
        // 何らかの処理
        x_ = rhs.x_;  // @@@ delete
        return *this;
    }

    Widget& operator=(Widget&& rhs) & noexcept  // OK lvalue修飾
    {
        // 何らかの処理
        x_ = rhs.x_;  // @@@ delete
        return *this;
    }
    // @@@ ignore begin
    explicit Widget(uint32_t x) : x_{x} {}
    uint32_t GetX() const noexcept { return x_; }

private:
    uint32_t x_{0};
    // @@@ ignore end
};
// @@@ sample end

TEST(ProgrammingConvention, assignment_operator)
{
    // @@@ sample begin 2:3

    Widget w0{1};
    Widget w1{2};

    // Widget{2} = w0;          lvalue修飾の効果でコンパイルエラー
    // Widget{3} = Widget{4};   lvalue修飾の効果でコンパイルエラー
    // @@@ sample end

    ASSERT_EQ(1, w0.GetX());
    ASSERT_EQ(2, w1.GetX());
}
}  // namespace OK
}  // namespace AssignmentOperator
namespace OverrideSample {
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_CLANG_OVERLOADED_VIRTUAL;
// @@@ sample begin 3:0

class Base {
public:
    virtual ~Base();                   // OK
    virtual void f(int32_t) noexcept;  // OK
    virtual void g() noexcept;         // OK
};

// Derived_0::fは、Base::fのオーバーライドのつもりであったが、タイポのため新たな関数の宣言、
// 定義になってしまった。この手のミスは、自分で気づくのは難しい
class Derived_0 : public Base {
public:
    virtual ~Derived_0();                // NG overrideが必要
    void f(uint32_t) noexcept;           // NG Derived_0:fはBase:fのオーバーライドではない
                                         //    virtualとoverrideやfinalがない
    virtual void g() noexcept override;  // OK
};

class Derived_1 : public Base {
public:
    // NG 下記が必要
    // virtual ~Derived_1() override;

// clang-format off
#if 0   // @@@ delete
    virtual void f(uint32_t) override;  // OK overrideと書いたことで、
                                        //    コンパイルエラーになりタイポに気づく
    virtual void f(uint32_t) final;     // OK finalと書いたことで、
                                        //    コンパイルエラーになりタイポに気づく
#endif  // @@@ delete
    // clang-format on
};

class Derived_2 : public Base {
public:
    virtual ~Derived_2() override;                    // OK Derived_2はfinalではない
    virtual void f(int32_t) noexcept override final;  // NG overrideは不要
    virtual void g() noexcept final;                  // OK これ以上オーバーライドしない
};
// @@@ sample end

SUPPRESS_WARN_END;
}  // namespace OverrideSample
namespace OverrideSample2 {
// @@@ sample begin 3:2

class Base {
public:
    virtual int32_t GetArg(int32_t a = 0) const noexcept { return a; }
    // @@@ ignore begin
    virtual ~Base() = default;
    // @@@ ignore end
};

class Derived : public Base {
public:
    // NG Base::GetArgのデフォルト引数と違う
    virtual int32_t GetArg(int32_t a = 1) const noexcept override { return a; }

    // @@@ ignore begin
    virtual ~Derived() override = default;
    // @@@ ignore end
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, different_default_param)
{
    // @@@ sample begin 3:3

    auto  d = Derived{};
    Base& b{d};

    // 同じオブジェクトであるにもかかわらず、その表層型でデフォルト引数の値が変わってしまう。
    ASSERT_EQ(0, b.GetArg());
    ASSERT_EQ(1, d.GetArg());
    // @@@ sample end
}
}  // namespace
}  // namespace OverrideSample2
