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

// @@@ sample begin 1:1

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
    // @@@ sample begin 1:2

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

// @@@ sample begin 1:3

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

namespace {
TEST(ProgrammingConvention, func_constructor)
{
    // clang-format off
    // @@@ sample begin 1:4

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
}  // namespace
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

    Widget{2} = w0;  // NG lvalue修飾無しのcopy代入演算子であるため、コンパイルできる
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
    virtual ~Derived_0();       // NG overrideが必要
    void f(uint32_t) noexcept;  // NG Derived_0:fはBase:fのオーバーライドではない
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
    virtual void g() noexcept final;  // OK これ以上オーバーライドしない
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

namespace OverloadSample {
// @@@ sample begin 4:0

// NGな例
class Base {
public:
    virtual ~Base() = default;
    void f() noexcept
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
};

class DerivedNG : public Base {
public:
    void f(int32_t a) noexcept  // NG DerivedNG::f(int32_t)がBase::fを隠す(可視範囲の縮小)
    {
        // @@@ ignore begin
        IGNORE_UNUSED_VAR(a);
        // @@@ ignore end
    }
};

void f() noexcept
{
    auto d = DerivedNG{};

    d.f(0);
#if 0
    d.f(); // NG DerivedNG::f(int32_t)がBase::fを隠す(可視範囲の縮小)ためコンパイルエラー
#endif
}

// DerivedNGの修正
class DerivedOK : public Base {
public:
    void f(int32_t a) noexcept
    {
        // @@@ ignore begin
        IGNORE_UNUSED_VAR(a);
        // @@@ ignore end
    }
    using Base::f;  // OK Base::fをDerivedOKに導入。
};

void g() noexcept
{
    auto d = DerivedOK{};

    d.f(0);
    d.f();  // OK usingにより、Base::fが見える
}
// @@@ sample end
}  // namespace OverloadSample

namespace OverloadCompatiArgs {

// @@@ sample begin 4:1

int32_t f(int32_t) { return 0; }
int32_t f(int16_t) { return 1; }
// @@@ sample end

TEST(ProgrammingConvention, overload_with_compatible_args)
{
    // @@@ sample begin 4:2

    auto i16 = int16_t{1};

    ASSERT_EQ(1, f(i16));        // f(int16_t)が呼ばれる
    ASSERT_EQ(0, f(i16 + i16));  // f(int32_t)が呼ばれる
    // @@@ sample end
}
}  // namespace OverloadCompatiArgs

namespace OverloadDelete {

// @@@ sample begin 4:3

// 実引数がdoubleを認めないパターン
int32_t f0(double) = delete;
int32_t f0(int32_t a) noexcept { return a / 2; }

// 実引数がint32_t以外を認めないパターン
template <typename T>
int32_t f1(T) = delete;
int32_t f1(int32_t a) noexcept { return a / 2; }

// 実引数がunsigned以外を認めないパターン
template <typename T, std::enable_if_t<!std::is_unsigned_v<T>>* = nullptr>  // C++17スタイル
uint64_t f2(T) = delete;

template <typename T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr>  // C++17スタイル
uint64_t f2(T t) noexcept
{
    uint64_t f2_impl(uint64_t) noexcept;

    // Tがsignedで、tが-1のような値の場合、f2_impl(uint64_t)の呼び出しによる算術変換により、
    // tは巨大な値に変換されるが、
    // Tがunsignedならば、f2_impl(uint64_t)の呼び出しによる算術変換は安全

    return f2_impl(t);
}

template <typename T>
uint64_t f3(T) = delete;

template <std::unsigned_integral T>  // C++20スタイル
uint64_t f3(T t) noexcept
{
    uint64_t ret = t;
    // 何らかの処理

    return ret;
}
// @@@ sample end

TEST(ProgrammingConvention, overload_with_delete)
{
    // @@@ sample begin 4:4

    char     c{'c'};
    int8_t   i8{1};
    int32_t  i32{1};
    uint32_t ui32{1};
    uint64_t ui64{1};
    double   d{1.0};

    f0(c);
    f0(i8);
    f0(i32);
    // f0(d);    呼び出そうとしたf0(double)はdeleteされているので意図通りエラー

    f1(i32);
    // f1(u32);  呼び出そうとしたf1<uint32_t>(uint32_t)はdeleteされているので意図通りエラー

    f2(ui32);
    f2(ui64);
    // f2(c);    呼び出そうとしたf2<char>(char)はdeleteされているので意図通りエラー
    // f2(i32);  呼び出そうとしたf2<int32_t>(int32_t)はdeleteされているので意図通りエラー
    // f3(i8);   呼び出そうとしたf3<int8_t>(int8_t)はdeleteされているので意図通りエラー
    f3(ui32);
    // @@@ sample end
    IGNORE_UNUSED_VAR(d);
}

uint64_t f2_impl(uint64_t a) noexcept { return a / 2; }
}  // namespace OverloadDelete

namespace OperatorOverloadSample {
// @@@ sample begin 5:0

class A0 {
public:
    operator bool() const noexcept  // NG intへの型変換が可能
    {
        return state_;
    }

private:
    bool state_{true};
};

class A1 {
public:
    explicit operator bool() const noexcept  // OK explicitすることで誤使用を避ける。
    {
        return state_;
    }

private:
    bool state_{true};
};

void f()
{
    auto a0 = A0{};
    auto a1 = A1{};

    std::cout << a0 + 1;  // NG コンパイルできてしまう。
#if 0
    std::cout << a1 + 1;  // OK 意図通りコンパイルエラー
#endif

    // @@@ ignore begin
    IGNORE_UNUSED_VAR(a1);
    // @@@ ignore end
}
// @@@ sample end
// @@@ sample begin 5:1

class Integer {
public:
    Integer(int32_t integer) noexcept
        : integer_{integer} {}  // int32_tの暗黙の型変換が必要なのでexplicitしない

    // copyコンストラクタ、copy代入演算子の定義
    Integer(Integer const&)            = default;
    Integer& operator=(Integer const&) = default;

    friend bool operator==(Integer lhs, Integer rhs) noexcept
    {
        return lhs.integer_ == rhs.integer_;
    }

    Integer& operator+=(Integer rhs) noexcept
    {
        integer_ += rhs.integer_;
        return *this;
    }

private:
    int32_t integer_;
};

inline bool operator!=(Integer lhs, Integer rhs) noexcept
{
    return !(lhs == rhs);  // operator==の活用
}

inline Integer operator+(Integer lhs, Integer rhs) noexcept
{
    lhs += rhs;  // operator+=の活用
    return lhs;
}

// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_USER_DEFINED_LITERAL;
SUPPRESS_WARN_CLANG_RESERVED_USER_DEFINED_LITERAL;
// @@@ sample begin 5:2

constexpr int32_t one_km{1000};

// ユーザ定義リテラル演算子の定義
constexpr int32_t operator""_kilo_meter(unsigned long long num_by_mk)  // OK
{
    return num_by_mk * one_km;
}

constexpr int32_t operator"" km(unsigned long long num_by_mk)  // NG STDでリザーブ
{
    return num_by_mk * one_km;
}

constexpr int32_t operator""_meter(unsigned long long num_by_m)  // OK
{
    return num_by_m;
}

constexpr int32_t operator""_m(unsigned long long num_by_m)  // NG 短すぎる
{
    return num_by_m;
}
// @@@ sample end

TEST(ProgrammingConvention, user_defined_literal)
{
    // @@@ sample begin 5:3

    auto km = int32_t{3_kilo_meter};  // ユーザ定義リテラル演算子の利用
    auto m  = int32_t{3000_meter};    // ユーザ定義リテラル演算子の利用

    ASSERT_EQ(m, km);
    // @@@ sample end
}
// @@@ sample end
SUPPRESS_WARN_END;
}  // namespace OperatorOverloadSample

namespace ArgumentSample {

enum class EnumArg { first, second, third };
class NotSmall;
class Small {};

// @@@ sample begin 6:0

void f(int32_t a, enum EnumArg b, NotSmall const& c, Small d, NotSmall const* e) noexcept
{
    // a : 基本型
    // b : enum
    // c : サイズが小さくないオブジェクトで、nullptrでないことが前提
    // d : サイズ小さいオブジェクト
    // e : サイズが小さくないオブジェクトを指すが、nullptrである場合も処理の対象

    if (e == nullptr) {
        // @@@ ignore begin
        // @@@ ignore end
    }
    else {
        // @@@ ignore begin
        // @@@ ignore end
    }

    // @@@ ignore begin
    IGNORE_UNUSED_VAR(a, b, c, d);
    // @@@ ignore end
}
// @@@ sample end
// @@@ sample begin 6:1

class A {
public:
    int32_t f0() noexcept { return a_++; }

    int32_t f1() noexcept { return a_--; }
    // @@@ ignore begin
    A() = default;

private:
    int32_t a_{0};
    // @@@ ignore end
};

void f(int32_t a0, int32_t a1) noexcept
{
    // @@@ ignore begin
    IGNORE_UNUSED_VAR(a0, a1);
    // @@@ ignore end
}

void g(A& a) noexcept
{
    // clang-format off
    f(a.f0(), a.f1());  // NG f0()、f1()が呼ばれる順番は未定義。

    auto a0 = a.f0();
    auto a1 = a.f1();
    f(a0, a1);          // OK f0()はf1()よりも先に呼ばれる。
    // clang-format on
}
// @@@ sample end
// @@@ sample begin 6:2

class B {
public:
    B(A const& rhs);
    B& operator=(A const& rhs);

private:
    int32_t b_{0};

    friend bool operator==(B const& lhs, B const& rhs) noexcept { return lhs.b_ == rhs.b_; }
};
// @@@ sample end

class D;

// @@@ sample begin 6:3

class C {
public:
    // clang-format off
    void SetValue(int32_t number_of_peaple);  // OK
//  void SetValue(int32_t);                   // NG 仮引数名を書く
    void SetValue(D const& d);                // OK
//  void SetValue(D const&);                  // NG 仮引数名を書く
//  int32_t GetValue(void) const;             // NG void不要
    int32_t GetValue() const;                 // OK
    // clang-format on
};

extern "C" int32_t XxxGetValue(void);  // OK Cからリンクされる
// @@@ sample end

template <typename T, size_t N>  // OK
constexpr size_t array_length(T const (&)[N]) noexcept
{
    return N;
}

// @@@ sample begin 6:4

class Base {
public:
    Base(char const* name) noexcept : name0_{name} {}
    char const* Name0() const noexcept { return name0_; }

    // @@@ ignore begin
    Base& operator=(Base const& rhs) = default;
    Base(Base const&)                = default;
    // @@@ ignore end
private:
    char const* name0_;
};

class Derived final : public Base {
public:
    Derived(char const* name0, char const* name1) noexcept : Base{name0}, name1_{name1} {}
    char const* Name1() const noexcept { return name1_; }

    // @@@ ignore begin
    Derived& operator=(Derived const& rhs) = default;
    Derived(Derived const&)                = default;
    // @@@ ignore end
private:
    char const* name1_;
};

std::vector<std::string> f(Base const* array, uint32_t n)  // NG 誤用しやすいシグネチャ
{
    auto ret = std::vector<std::string>{n};

    std::transform(array, array + n, ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

    return ret;
}

std::vector<std::string> g(Base const array[10], uint32_t n)  // NG 誤用しやすいシグネチャ
{
    // str_arrayは一見、配列に見えるが、実際はポインタであるため、
    // この関数のシグネチャはf(Base const* str_array, uint32_t n)と同じ。
    // 配列の長さに見える10はシンタックス上の意味を持たない。
    auto ret = std::vector<std::string>{n};

    std::transform(array, array + n, ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

    return ret;
}
// @@@ sample end

namespace {

TEST(ProgrammingConvention, use_convert_to_ptr)
{
    // clang-format off
    // @@@ sample begin 6:5

    Base    b[]{"0", "0"};
    Derived d[]{{"0", "1"}, {"2", "3"}};

    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f(b, array_length(b)));  // OK これは良いが
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g(b, array_length(b)));  // OK これは良いが

    // 本来なら、下記のようになるべきだが、
    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), f(d, array_length(d)));  // NG
    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), g(d, array_length(d)));  // NG

    // レイアウトずれにより、下記のようになる
    ASSERT_EQ((std::vector<std::string>{"0", "1"}), f(d, array_length(d)));  // NG
    ASSERT_EQ((std::vector<std::string>{"0", "1"}), g(d, array_length(d)));  // NG
    // @@@ sample end
    // clang-format on
}
}  // namespace

// @@@ sample begin 6:6

// ポインタではなく、配列へのリファレンスを使用することで、
// 上記のようなバグを避けることができる

std::vector<std::string> f_ref_2(Base const (&array)[2])  // OK 配列へのリファレンス
{
    auto ret = std::vector<std::string>{array_length(array)};

    // arrayの型はポインタではなく、リファレンスなのでstd::endが使える
    std::transform(array, std::end(array), ret.begin(),
                   [](Base const& b) noexcept { return b.Name0(); });

    return ret;
}

template <size_t N>                                       // 配列の長さの型はsize_t
std::vector<std::string> f_ref_n(Base const (&array)[N])  // OK 配列へのリファレンス
{
    auto ret = std::vector<std::string>{N};

    std::transform(array, std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

    return ret;
}

template <typename T, size_t N>                      // 配列の長さの型はsize_t
std::vector<std::string> g_ref(T const (&array)[N])  // OK 配列へのリファレンス
{
    auto ret = std::vector<std::string>{N};

    std::transform(array, std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

    return ret;
}

template <typename T, size_t N>  // std::arrayの第2パラメータの型はsize_t
std::vector<std::string> h_ref(std::array<T, N> const& array)  // OK std::arrayへのリファレンス
{
    auto ret = std::vector<std::string>{N};

    std::transform(std::begin(array), std::end(array), ret.begin(),
                   [](auto& b) noexcept { return b.Name0(); });

    return ret;
}

// NULLを渡す必要がある場合、配列へのリファレンスの代わりに、
// 配列へのポインタを使うことができる
template <typename T, uint32_t N>
std::vector<std::string> g_ptr(T const (*array)[N])  // OK
{
    if (array == nullptr) {
        return std::vector<std::string>{};
    }

    auto ret = std::vector<std::string>{N};

    std::transform(*array, std::end(*array), ret.begin(),
                   [](auto& b) noexcept { return b.Name0(); });

    return ret;
}
// @@@ sample end

namespace {

TEST(ProgrammingConvention, not_use_convert_to_ptr)
{
    // @@@ sample begin 6:7
    Base    b[]{"0", "0"};
    Derived d[]{{"0", "1"}, {"2", "3"}};
    auto    d2 = std::array<Derived, 2>{Derived{"0", "1"}, Derived{"2", "3"}};

    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f_ref_2(b));  // OK
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f_ref_n(b));  // OK
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g_ref(b));    // OK

    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), f_ref_2(d));  OK 誤用なのでコンパイルエラー
    ASSERT_EQ((std::vector<std::string>{"0", "2"}), g_ref(d));   // OK
    ASSERT_EQ((std::vector<std::string>{"0", "2"}), h_ref(d2));  // OK

    // 配列へのポインタを使う場合
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g_ptr(&b));  // OK

    Derived(*d_null)[3]{nullptr};
    ASSERT_EQ((std::vector<std::string>{}), g_ptr(d_null));  // OK
    // @@@ sample end
}
}  // namespace
// @@@ sample begin 6:8

int32_t default_arg{0};
int32_t get_default_arg(int32_t a = default_arg) noexcept { return a; }
// @@@ sample end

namespace {
TEST(ProgrammingConvention, call_get_default_arg)
{
    // @@@ sample begin 6:9

    ASSERT_EQ(0, get_default_arg());  // default_arg == 0

    default_arg = 2;

    ASSERT_EQ(2, get_default_arg());  // default_arg == 2
    // @@@ sample end
}
}  // namespace

namespace Sub {
// @@@ sample begin 6:10

void f0(std::unique_ptr<std::string> const& str)  // NG *strは書き換え可能
{
    *str = "it can be changed";

#if 0  // strはconstなので以下はできない
    str = std::make_unique<std::string>("haha");
#endif
}

void f1(std::string& str)  // OK
{
    str = "it can be changed";
}

void f2(std::string const& str)  // OK
{
#if 0  // strは変更できない
    str = "it can NOT be changed";
#endif
}

void g()
{
    auto s = std::make_unique<std::string>("hehe");

    // clang-format off
    f0(s);   // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f1(*s);  // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f2(*s);  // sも、sが指しているstd::stringオブジェクトも変更されない
    // clang-format on
}
// @@@ sample end
}  // namespace Sub
}  // namespace ArgumentSample

namespace AutoVariable {

int32_t get_index() noexcept { return 0; }

class Widget {
public:
    enum Status { None, Success, Warn, Fail };

    static Widget& InstConst() noexcept { return Inst(); }

    static Widget& Inst() noexcept
    {
        static Widget inst;
        return inst;
    }

    Status GetStatus() const noexcept { return status_; }

    void DoSomething() noexcept {}

    void DoSomething(Status s) noexcept { status_ = s; }

private:
    explicit Widget() noexcept {}
    Status status_{None};
};

void f(int32_t max) noexcept
{
    // @@@ sample begin 7:0

    int32_t a, b;  // NG 一度に2つの変数定義
    int32_t index;

    // Do something
    // @@@ ignore begin
    // @@@ ignore end

    index = get_index();                    // NG 定義と使用箇所が離れている
    int32_t index2{get_index()};            // OK
    auto    index3 = get_index();           // OK AAA
    auto    index4 = int32_t{get_index()};  // OK 型を明示したAAA

    int32_t i;

    for (i = 0; i < max; ++i) {  // NG 定義と使用箇所が離れている
        // Do something
    }

    for (int32_t i{0}; i < max; ++i) {  // OK
        // Do something
        // @@@ ignore begin
        // @@@ ignore end
    }

    for (auto i = 0; i < max; ++i) {  // OK AAAスタイル
        // Do something
        // @@@ ignore begin
        // @@@ ignore end
    }

    // @@@ ignore begin
    // @@@ ignore end

    auto& w0 = Widget::Inst();  // if文後にはw0を使用しないならばNG
    if (w0.GetStatus() == Widget::Success) {
        w0.DoSomething();
    }
    else {
        w0.DoSomething(Widget::None);
    }
    // この後w0を使用しない

    // @@@ ignore begin
    // @@@ ignore end

    if (auto& w1 = Widget::Inst(); w1.GetStatus() == Widget::Success) {  // OK C++17より使用可能
        w1.DoSomething();
    }
    else {
        w1.DoSomething(Widget::None);
    }

    // @@@ ignore begin
    // @@@ ignore end

    auto const& w2 = Widget::InstConst();  // switch文後にw2を使用しないならばNG
    switch (w2.GetStatus()) {
    case Widget::Success:
        // Do something
        break;
        // @@@ ignore begin
    case Widget::Fail:
        // Do something
        break;
    case Widget::Warn:
        // Do something
        break;
        // @@@ ignore end
    default:
        // Do something
        break;
    }
    // この後w2を使用しない

    // @@@ ignore begin
    // @@@ ignore end

    switch (auto const& w3 = Widget::InstConst(); w3.GetStatus()) {  // OK C++17より使用可能
    case Widget::Success:
        // Do something
        break;
        // @@@ ignore begin
    case Widget::Fail:
        // Do something
        break;
    case Widget::Warn:
        // Do something
        break;
        // @@@ ignore end
    default:
        // Do something
        break;
    }
    // @@@ sample end

    IGNORE_UNUSED_VAR(a, b, index, index2, index3, index4, i);
}
}  // namespace AutoVariable

namespace ReturnSample {

// @@@ sample begin 8:0

auto f(int32_t a, int32_t b) noexcept -> decltype(a + b)  // NG
{
    return a + b;
}

template <typename T>
auto f(T a, T b) noexcept -> decltype(a + b)  // OK 後置構文以外に方法がない
{
    return a + b;  // T = uint8_tとすると、a + bの型はint32_t
}
// @@@ sample end
// @@@ sample begin 8:1

void g0(int32_t a, int32_t b, int32_t& quotient, int32_t& remainder)  // NG
{
    quotient  = a / b;
    remainder = a % b;
}

int32_t g1(int32_t a, int32_t b, int32_t& remainder)  // NG
{
    remainder = a % b;
    return a / b;
}

std::pair<int32_t, int32_t> g_pair(int32_t a, int32_t b)  // OK
{
    return {a / b, a % b};
}

struct Result {
    int32_t quotient;
    int32_t remainder;
};

Result g_struct(int32_t a, int32_t b)  // OK
{
    return {a / b, a % b};
}
// @@@ sample end

namespace {
TEST(ProgrammingConvention, return_pair)
{
    // @@@ sample begin 8:2

    {
        int32_t quotient;
        int32_t remainder;
        g0(7, 3, quotient, remainder);  // NG quotient、remainderが戻り値かどうかわかりづらい
        ASSERT_EQ(2, quotient);
        ASSERT_EQ(1, remainder);
    }
    {
        int32_t remainder;
        int32_t quotient{g1(7, 3, remainder)};  // NG remainderが戻り値かどうかわかりづらい
        ASSERT_EQ(2, quotient);
        ASSERT_EQ(1, remainder);
    }
    {
        auto ret = g_pair(7, 3);  // OK
        ASSERT_EQ(2, ret.first);
        ASSERT_EQ(1, ret.second);
    }
    {
        auto [quotient, remainder] = g_struct(7, 3);  // OK C++17 構造化束縛
        ASSERT_EQ(2, quotient);
        ASSERT_EQ(1, remainder);
    }
    {
        auto ret = g_struct(7, 3);  // OK
        ASSERT_EQ(2, ret.quotient);
        ASSERT_EQ(1, ret.remainder);
    }
    // @@@ sample end

    {
        int32_t quotient;
        int32_t remainder;
        g0(6, 4, quotient, remainder);
        ASSERT_EQ(1, quotient);
        ASSERT_EQ(2, remainder);
    }
    {
        int32_t remainder;
        int32_t quotient{g1(6, 4, remainder)};
        ASSERT_EQ(1, quotient);
        ASSERT_EQ(2, remainder);
    }
    {
        auto [quotient, remainder] = g_pair(6, 4);
        ASSERT_EQ(1, quotient);
        ASSERT_EQ(2, remainder);
    }
    {
        auto [quotient, remainder] = g_struct(6, 4);
        ASSERT_EQ(1, quotient);
        ASSERT_EQ(2, remainder);
    }
}
}  // namespace

// @@@ sample begin 8:3

bool h0(int32_t a, int32_t b, int32_t& remainder)  // NG
{
    if (b == 0) {
        return false;
    }

    remainder = a % b;

    return true;
}

int32_t h1(uint32_t a, uint32_t b)  // NG 余りが-1になる場合(外れ値)、エラー通知
{
    if (b == 0) {
        return -1;
    }

    return a % b;
}

std::pair<bool, int32_t> h_pair(int32_t a, int32_t b)  // NG
{
    if (b == 0) {
        return {false, 0};
    }

    return {true, a % b};
}

struct Result2 {
    bool    is_success;
    int32_t remainder;
};

Result2 h_struct(int32_t a, int32_t b)  // NG
{
    if (b == 0) {
        return {false, 0};
    }

    return {true, a % b};
}

std::optional<int32_t> h_optional(int32_t a, int32_t b)  // OK
{
    if (b == 0) {
        return std::nullopt;
    }

    return a % b;
}
// @@@ sample end
namespace {
TEST(ProgrammingConvention, return_optional)
{
    // @@@ sample begin 8:4

    {
        int32_t remainder;

        auto result = h0(7, 0, remainder);
        ASSERT_FALSE(result);  // エラー時にremainderが有効か否かわからない
    }
    {
        auto remainder = h1(7, 0);
        ASSERT_EQ(-1, remainder);  // エラー通知がわかりづらい
    }
    {
        auto [result, remainder] = h_pair(7, 0);
        ASSERT_FALSE(result);  // エラー時にremainderが有効か否かわからない
    }
    {
        auto [result, remainder] = h_struct(7, 0);
        ASSERT_FALSE(result);  // エラー時にremainderが有効か否かわからない
    }
    {
        auto result = h_optional(7, 0);
        ASSERT_FALSE(result);

        result = h_optional(7, 4);
        ASSERT_TRUE(result);
        ASSERT_EQ(3, *result);  // 成功時の値取り出し
    }
    // @@@ sample end

    {
        int32_t remainder;

        auto result = h0(7, 4, remainder);
        ASSERT_TRUE(result);
        ASSERT_EQ(3, remainder);
    }
    {
        auto remainder = h1(7, 4);
        ASSERT_EQ(3, remainder);
    }
    {
        auto [result, remainder] = h_pair(7, 4);
        ASSERT_TRUE(result);
        ASSERT_EQ(3, remainder);
    }
    {
        auto [result, remainder] = h_struct(7, 4);
        ASSERT_TRUE(result);
        ASSERT_EQ(3, remainder);
    }
}
}  // namespace
}  // namespace ReturnSample

namespace ReentrantSample {
// @@@ sample begin 9:0

int32_t var{0};

int32_t f() noexcept  // リエントラントでない関数f()
{
    return ++var;
}

int32_t f(int32_t& i) noexcept  // リエントラントな関数f()
{
    return ++i;
}
// @@@ sample end
}  // namespace ReentrantSample
namespace ExceptionHandlingSample {

class Base {
public:
    // @@@ ignore begin
    Base()          = default;
    virtual ~Base() = default;
    // @@@ ignore end
    virtual int32_t f() const noexcept
    {
        // @@@ ignore begin
        return 0;
        // @@@ ignore end
    }
};

// @@@ sample begin 10:0

int32_t f() noexcept;  // OK fはno-fail保証

class Derived : public Base {
    // @@@ ignore begin
public:
    Derived()          = default;
    virtual ~Derived() = default;
    // @@@ ignore end
    // オブジェクトの状態を変えず(const)、エクセプションを発生させず(noexcept)
    // f()の最後(final)のoverride
    virtual int32_t f() const noexcept final
    {
        // @@@ ignore begin
        return 1;
        // @@@ ignore end
    }
};
// @@@ sample end
// @@@ sample begin 10:1

// clang-format off
struct ExceptionA : std::exception {};
struct ExceptionB : ExceptionA {};
struct ExceptionX : std::exception {};
// clang-format on

void order_of_catch() noexcept
{
    try {
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (ExceptionB const& e) {  // ExceptionAの前に書く。
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (ExceptionA const& e) {  // std::exceptionの前に書く。
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (ExceptionX const& e) {  // std::exceptionの前に書く。
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (std::exception const& e) {  // catch(...)の前に書く。
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (...) {  // 必ず一番最後に書く。
        // @@@ ignore begin
        // @@@ ignore end
    }
}

void order_of_catch_with_try() noexcept
try {  // 関数tryブロック
    // @@@ ignore begin
    // @@@ ignore end
}
catch (ExceptionB const& e) {  // ExceptionAの前に書く。
    // @@@ ignore begin
    // @@@ ignore end
}
catch (ExceptionA const& e) {  // std::exceptionの前に書く。
    // @@@ ignore begin
    // @@@ ignore end
}
catch (ExceptionX const& e) {  // std::exceptionの前に書く。
    // @@@ ignore begin
    // @@@ ignore end
}
catch (std::exception const& e) {  // catch(...)の前に書く。
    // @@@ ignore begin
    // @@@ ignore end
}
catch (...) {  // 必ず一番最後に書く。
    // @@@ ignore begin
    // @@@ ignore end
}
// @@@ sample end

// @@@ sample begin 10:2

int32_t f0()  // noexceptではないため、エクセプションを発生させることがある。
{
    // @@@ ignore begin
    return 1;
    // @@@ ignore end
}

int32_t f1() noexcept
{
    // @@@ ignore begin
    return 1;
    // @@@ ignore end
}

#if __cplusplus < 201703L  // 以下のコードはC++14以前ではコンパイルできるが、
                           // C++17以降ではコンパイルエラー
#ifndef __clang__          // @@@ delete
int32_t (*f_ptr0)() noexcept = &f0;  // NG f_ptr0()はnoexceptだが、
                                     //    f0はエクセプションを発生させる可能性がある。
#endif  // @@@ delete
#endif
int32_t (*f_ptr1)() noexcept = &f1;  // OK
int32_t (*f_ptr2)()          = &f0;  // OK
int32_t (*f_ptr3)()          = &f1;  // OK f1はエクセプションを発生させない。

class A {
public:
    int32_t f0()  // noexceptではないため、エクセプションを発生させることがある。
    {
        // @@@ ignore begin
        return 1;
        // @@@ ignore end
    }

    int32_t f1() noexcept
    {
        // @@@ ignore begin
        return 1;
        // @@@ ignore end
    }
};

#if __cplusplus < 201703L  // 以下のコードはC++14以前ではコンパイルできるが、
                           // C++17以降ではコンパイルエラー
#ifndef __clang__          // @@@ delete
int32_t (A::*mf_ptr0)() noexcept = &A::f0;  // NG mf_ptr0()はnoexceptだが、
                                            //    f0はエクセプションを発生させる可能性がある。
#endif  // @@@ delete
#endif
int32_t (A::*mf_ptr1)() noexcept = &A::f1;  // OK
int32_t (A::*mf_ptr2)()          = &A::f0;  // OK
int32_t (A::*mf_ptr3)()          = &A::f1;  // OK f1はエクセプションを発生させない。

// @@@ sample end
}  // namespace ExceptionHandlingSample

namespace BusyLoopSample {

bool xxx_flag;

// @@@ sample begin 11:0

// NG イベントドリブンにするべき
void wait_busily() noexcept
{
    while (1) {
        sleep(1);
        if (xxx_flag) {
            // @@@ ignore begin
            // @@@ ignore end
            break;
        }
    }

    // @@@ ignore begin
    // @@@ ignore end
}

// OK selectでイベント発生を待つ。
void wait_event(fd_set const& rfds, uint32_t wait_sec) noexcept
{
    while (1) {
        auto rfds2 = rfds;
        auto tv    = timeval{wait_sec, 0};

        auto retval = select(1, &rfds2, 0, 0, &tv);

        // @@@ ignore begin
        IGNORE_UNUSED_VAR(retval);
        // @@@ ignore end
    }

    // @@@ ignore begin
    // @@@ ignore end
}
// @@@ sample end
}  // namespace BusyLoopSample
