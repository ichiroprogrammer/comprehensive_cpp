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

namespace OverloadSample {
// @@@ sample begin 0:0

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

// @@@ sample begin 0:1

int32_t f(int32_t) { return 0; }
int32_t f(int16_t) { return 1; }
// @@@ sample end

TEST(ProgrammingConvention, overload_with_compatible_args)
{
    // @@@ sample begin 0:2

    auto i16 = int16_t{1};

    ASSERT_EQ(1, f(i16));        // f(int16_t)が呼ばれる
    ASSERT_EQ(0, f(i16 + i16));  // f(int32_t)が呼ばれる
    // @@@ sample end
}
}  // namespace OverloadCompatiArgs

namespace OverloadDelete {

// @@@ sample begin 0:3

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
    // @@@ sample begin 0:4

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
// @@@ sample begin 1:0

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
// @@@ sample begin 1:1

class Integer {
public:
    Integer(int32_t integer) noexcept : integer_{integer} {}  // int32_tの暗黙の型変換が必要なのでexplicitしない

    // copyコンストラクタ、copy代入演算子の定義
    Integer(Integer const&)            = default;
    Integer& operator=(Integer const&) = default;

    friend bool operator==(Integer lhs, Integer rhs) noexcept { return lhs.integer_ == rhs.integer_; }

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
// @@@ sample begin 1:2

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
    // @@@ sample begin 1:3

    auto km = int32_t{3_kilo_meter};  // ユーザ定義リテラル演算子の利用
    auto m  = int32_t{3000_meter};    // ユーザ定義リテラル演算子の利用

    ASSERT_EQ(m, km);
    // @@@ sample end
}
// @@@ sample end
SUPPRESS_WARN_END;
}  // namespace OperatorOverloadSample

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
    // @@@ sample begin 2:0

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

namespace ReentrantSample {
// @@@ sample begin 3:0

int32_t var{0};

int32_t f() noexcept  // スレッドセーフでない関数f()
{
    return ++var;
}

int32_t f(int32_t& i) noexcept  // スレッドセーフな関数f()
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
// @@@ sample end
// @@@ sample begin 4:0

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
// @@@ sample begin 4:1

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

// @@@ sample begin 4:2

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

#if __cplusplus < 201703L            // 以下のコードはC++14以前ではコンパイルできるが、
                                     // C++17以降ではコンパイルエラー
#ifndef __clang__                    // @@@ delete
int32_t (*f_ptr0)() noexcept = &f0;  // NG f_ptr0()はnoexceptだが、
                                     //    f0はエクセプションを発生させる可能性がある。
#endif                               // @@@ delete
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

#if __cplusplus < 201703L                   // 以下のコードはC++14以前ではコンパイルできるが、
                                            // C++17以降ではコンパイルエラー
#ifndef __clang__                           // @@@ delete
int32_t (A::*mf_ptr0)() noexcept = &A::f0;  // NG mf_ptr0()はnoexceptだが、
                                            //    f0はエクセプションを発生させる可能性がある。
#endif                                      // @@@ delete
#endif
int32_t (A::*mf_ptr1)() noexcept = &A::f1;  // OK
int32_t (A::*mf_ptr2)()          = &A::f0;  // OK
int32_t (A::*mf_ptr3)()          = &A::f1;  // OK f1はエクセプションを発生させない。

// @@@ sample end
}  // namespace ExceptionHandlingSample

namespace BusyLoopSample {

bool xxx_flag;

// @@@ sample begin 5:0

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
