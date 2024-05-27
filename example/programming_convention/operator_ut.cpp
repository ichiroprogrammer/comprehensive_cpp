#include <sys/socket.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <type_traits>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace OperatorPrioritySample {
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_PARENTHESES;

// 変数をvolatile にしたのはscan-build対策
bool f(int8_t a, volatile int8_t& b, volatile int8_t& c, volatile int8_t& d, int8_t e,
       int8_t f) noexcept
{
    // @@@ sample begin 0:0

    // 論理演算子例
    if (a < b && c < d || e < f)  // NG 優先順位がわからない
    {
        // @@@ ignore begin
        return true;
        // @@@ ignore end
    }

    if (((a < b) && (c < d)) || (e < f))  // OK
    {
        // @@@ ignore begin
        return true;
        // @@@ ignore end
    }

    // シフト演算子例
    auto a0 = b << 16 + 1;    // NG
    auto a1 = b << (16 + 1);  // OK
    auto a2 = (b << 16) + 1;  // OK

    // ビット演算ではないが
    std::cout << a0 + 1;    // NG
    std::cout << (a1 + 1);  // OK

    // 三項演算子例
    // clang-format off
    auto e0 = a ? b : c = d;      // NG
    auto e1 = ((a ? b : c) = d);  // OK
    auto e2 = (a ? b : (c = d));  // OK 上記NG式と同じ意味
    // @@@ sample end
    // clang-format on

    IGNORE_UNUSED_VAR(a2, e0, e1, e2);

    return false;
}

namespace {
TEST(ProgrammingConvention, operator_priority)
{
    // @@@ sample begin 1:0
    {
        auto a = 4;

        a = a * 3 / 2;
        ASSERT_EQ(6, a);
    }
    {
        auto a = 4;

        a *= 3 / 2;  // この式は、a = a * 3 / 2と等価ではない
        ASSERT_EQ(4, a);
    }
    // @@@ sample end
}
}  // namespace
}  // namespace OperatorPrioritySample

namespace OperatorEqualSample {

SUPPRESS_WARN_PARENTHESES;
SUPPRESS_WARN_GCC_SEQ_POINT;
SUPPRESS_WARN_CLANG_UNSEQUENCED;

// 変数をvolatile にしたのはscan-build対策
bool f(volatile int32_t a, volatile int32_t b, volatile int32_t c) noexcept
{
    // @@@ sample begin 2:0

    a = b = 0;              // OK
    b     = (a += 1) + 2;   // NG
    b     = (a++) + (c++);  // NG

    b = b++;  // NG unary operators assign itself.

    ++a;         // OK
    auto i = a;  // OK

    a = 0;  // OK
    // @@@ sample end

    auto fd1 = 0;

    // @@@ sample begin 2:1

    if (c = b) {  // NG ifの条件文の中で代入
        return 0;
    }

    if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // OK このような場合は代入していることが明確
        return false;
    }

    if (auto fd2 = socket(AF_INET, SOCK_STREAM, 0); fd2 < 0) {  // OK C++17
        return false;
    }
    else {
        // fd2を使った処理
        // @@@ ignore begin
        IGNORE_UNUSED_VAR(fd2);
        // @@@ ignore end
    }
    // @@@ sample end

    return i + b < fd1;
}

SUPPRESS_WARN_END;
}  // namespace OperatorEqualSample

namespace LogicalOperatorSample {

void f(uint32_t a, uint32_t b) noexcept
{
    // @@@ sample begin 3:0

    if (a == 0 && ++b > 3) {  // NG ++bが上記の副作用
        // @@@ ignore begin
        return;
        // @@@ ignore end
    }

    // ↑のような記述は、↓とは意味が違う
    ++b;
    if (a == 0 && b > 3) {  // OK
        // @@@ ignore begin
        return;
        // @@@ ignore end
    }

    if (a == 0) {  // OK 上記NGのif文と同じ意味
        ++b;
        if (b > 3) {
            // @@@ ignore begin
            return;
            // @@@ ignore end
        }
    }
    // @@@ sample end
}
}  // namespace LogicalOperatorSample

namespace TernaryOperatorSample {

int f(bool xxx) noexcept
{
    // @@@ sample begin 4:0

    int const a0{xxx ? 3 : 4};  // OK constで定義、初期化

    int a1;  // NG a1をconstにできない
             //    定義と初期が分離してしまう
    if (xxx) {
        a1 = 3;
    }
    else {
        a1 = 4;
    }
    // @@@ sample end

    return a0 + a1;
}

}  // namespace TernaryOperatorSample

namespace MemoryAllocSample {

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_DEL_INCOMP;

#if 0
class A;

#else
class A {
public:
    A() = default;
};
#endif

// @@@ sample begin 5:0

void deleteA(A* a_ptr) noexcept
{
    // Aが不完全型だった場合、deleteAは、A::~A()にアクセスできないため、A::~A()は呼び出されない
    // これはリソースリークにつながる
    delete a_ptr;
}

// やむを得ず、deleteAのような関数を作る場合、下記のようにstatic_assertをdelete行の直前に書く
// こうすることによりAが不完全型であった場合、コンパイルエラーとなる
void deleteA2(A* a_ptr) noexcept
{
    static_assert(sizeof(*a_ptr) != 0, "incomplete type");
    delete a_ptr;
}

// やむを得ず、deleteAのような関数を作る場合、std::unique_ptr<>を使用することもできる
// こうすることによりAが不完全型であった場合、コンパイルエラーとなる
void deleteA3(A* a_ptr) noexcept { std::unique_ptr<A> a(a_ptr); }
// @@@ sample end

// @@@ sample begin 5:1

void delete_ptr(void* v_ptr) noexcept
{
    // NG
    // 任意の型のポインタは、キャストすること無しでこの関数に渡すことができる
    // そのポインタがクラス型であった場合でも、void*として扱われるため、
    // そのクラスのデストラクタは呼び出されない
    delete v_ptr;
}

void deleteA4(A* ptr) noexcept
{
    delete_ptr(ptr);  // NG ptrはvoid*へ暗黙のキャストが行われる
                      //    delete_ptrでは、A::~A()は呼び出されない
}
// @@@ sample end

void f(A* ptr) noexcept
{
    // @@@ sample begin 5:2

    if (ptr != nullptr) {  // NG nullptrとの比較は不要
        delete ptr;
    }

    // @@@ ignore begin
}

void g(A* ptr) noexcept
{
    // @@@ ignore end

    delete ptr;  // OK ptrがnullptrでも問題ない
    // @@@ sample end
}

}  // namespace MemoryAllocSample

namespace SizeofSample {

SUPPRESS_WARN_CLANG_UNEVALUATED_EXPRESSION;
SUPPRESS_WARN_CLANG_UNUSED_INTERNAL_DECL;

uint8_t f() noexcept
{
    // @@@ sample begin 6:0

    uint8_t  a = 0;
    uint8_t* b = &a;

    auto s_0 = sizeof(uint8_t);  // NG aのサイズをs_0に代入したい場合
    auto s_1 = sizeof(a);        // OK aのサイズをs_1に代入したい場合
    auto s_2 = sizeof(*b);       // OK *bのサイズをs_2に代入したい場合
    // @@@ sample end

    IGNORE_UNUSED_VAR(b, s_0, s_1, s_2);

    // @@@ sample begin 6:1

    a = 0;

    auto size_3 = sizeof(++a);  // NG  おそらく意図通りには動かない
                                // この行でもa == 0(++aは効果がない)
    // @@@ sample end

    IGNORE_UNUSED_VAR(size_3);

    return a;
}

// @@@ sample begin 6:2

// 下記のようなsizeofディスパッチはC++03ではよく使われたが、
// C++11ではtype_traitsを使えば、もっとスマートに実装できる
struct True {
    uint8_t temp[2];
};
struct False {
    uint8_t temp[1];
};

constexpr True  sizeof_dispatch(int32_t);
constexpr False sizeof_dispatch(...);
// @@@ sample end

void f(int) noexcept
{
    // @@@ sample begin 6:3

    static_assert(sizeof(sizeof_dispatch(int{})) == sizeof(True), "int32_t is int");
    static_assert(sizeof(sizeof_dispatch(std::string{})) != sizeof(True), "int32_t is not string");

    // 上記はC++11では下記のように実装すべき
    static_assert(std::is_same_v<int, int32_t>, "int32_t is int");
    static_assert(!std::is_same_v<std::string, int32_t>, "int32_t is not string");

    // @@@ sample end
}

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_SIZEOF_ARRAY_ARG;

// @@@ sample begin 6:4

void f(int8_t arg_array0[5], int8_t arg_array1[], int8_t (&arg_array2)[5]) noexcept
{
    int8_t* ptr;
    int8_t  array[5];

    // arg_array0、arg_array1の型は、int8_t*
    // 従って、sizeof(arg_array0)の値は、sizeof(int8_t) * 5ではなく、sizeof(int8_t*)である

    // 64bit環境でコンパイルポインタサイズは8バイト
    static_assert(8 == sizeof(arg_array0), "arg_array0 is a pointer but an array");
    static_assert(8 == sizeof(arg_array1), "arg_array1 is a pointer but an array");
    static_assert(5 == sizeof(arg_array2), "arg_array2 is an array");
    static_assert(8 == sizeof(ptr), "ptr must be 8 bytes on 64bit environment");
    static_assert(5 == sizeof(array), "int8_t[5] is 5 bytes");
}
// @@@ sample end
SUPPRESS_WARN_END;

namespace {
TEST(ProgrammingConvention, SizeofArrayArg)
{
    int8_t arg_array0[5];

    f(arg_array0, arg_array0, arg_array0);
}
}  // namespace
}  // namespace SizeofSample

namespace PointerOpSample {

SUPPRESS_WARN_END;

void f() noexcept
{
    // @@@ sample begin 7:0

    int8_t  a0[5];
    int8_t  a1[5];
    int8_t* end0{&a0[5]};
    int8_t* end1{&a1[5]};

    for (int8_t* curr{a0}; curr < end0;  // OK currもend0もa0のどこかを指している
         ++curr) {
        *curr = 0;
    }

    for (int8_t* curr{a0}; curr < end1;  // NG currとend1は別々のオブジェクトを指している
         ++curr) {
        *curr = 0;
    }
    // @@@ sample end
}
}  // namespace PointerOpSample

// @@@ sample begin 8:0

class Base {
public:
    virtual ~Base() = default;
    // @@@ ignore begin
    // @@@ ignore end
};

class Derived_0 : public Base {
    // @@@ ignore begin
    // @@@ ignore end
};

class Derived_1 : public Base {
    // @@@ ignore begin
    // @@@ ignore end
};

// @@@ ignore begin
namespace {

Base& factory(int num) noexcept
{
    static Base      b;
    static Derived_0 d0;
    static Derived_1 d1;

    switch (num) {
    case 0:
        return b;
    case 1:
        return d0;
    case 2:
    default:
        return d1;
    }
}

TEST(ProgrammingConvention, typeid_name)
{
    auto& b0 = factory(0);
    ASSERT_EQ("4Base", std::string{typeid(b0).name()});

    auto& b1 = factory(1);
    ASSERT_EQ("9Derived_0", std::string{typeid(b1).name()});

    auto& b2 = factory(2);
    ASSERT_EQ("9Derived_1", std::string{typeid(b2).name()});
}

// @@@ ignore end

// NGの例
void b_do_something(Base const& b) noexcept
{
    auto name = std::string_view{typeid(b).name()};

    // bの実際の型を使った場合分けによる最悪のコード
    // dynamic_castによる場合分けも、下記のコードより大きく改善するわけではない
    if (name == "4Base") {  // マングリングされたBase
        // @@@ ignore begin
        // @@@ ignore end
    }
    else if (name == "9Derived_0") {  // マングリングされたDerived_0
        // @@@ ignore begin
        // @@@ ignore end
    }
    else if (name == "9Derived_1") {  // マングリングされたDerived_1
        // @@@ ignore begin
        // @@@ ignore end
    }
    else {
        assert(false);
    }
}
// @@@ sample end

TEST(ProgrammingConvention, typeid_case)
{
    auto& b = factory(0);  // Base、Derived_0、Derived_1を生成する

    b_do_something(b);
}
}  // namespace

namespace Polymorphic {

// @@@ sample begin 8:1

// OKの例
// 上記のb_do_somethingにポリモーフィズムを適用しリファクタリング
class Base {
public:
    void DoSomething() noexcept { do_something(); }
    // @@@ ignore begin
    virtual ~Base() = default;
    // @@@ ignore end
private:
    virtual void do_something() noexcept
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
};

class Derived_0 : public Base {
private:
    virtual void do_something() noexcept override
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
    // @@@ ignore begin
    // @@@ ignore end
};

class Derived_1 : public Base {
public:
    virtual void do_something() noexcept override
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
    // @@@ ignore begin
    // @@@ ignore end
};

// virtual Base::do_something()により醜悪なswitchが消えた
void b_do_something(Base& b) noexcept { b.DoSomething(); }
// @@@ sample end

TEST(ProgrammingConvention, refacotered_typeid_case)
{
    auto b = Base{};

    b_do_something(b);
}
}  // namespace Polymorphic
namespace CastSample {

// @@@ sample begin 9:0
class Base {
    // @@@ ignore begin
    // @@@ ignore end
};

class Derived : public Base {
    // @@@ ignore begin
    // @@@ ignore end
};

void f() noexcept
{
    auto  d     = Derived{};
    Base* b_ptr = &d;  // ここまでは良い

    auto d_ptr = static_cast<Derived*>(b_ptr);  // ダウンキャスト、動作保証はない

    IGNORE_UNUSED_VAR(d_ptr);  // @@@ delete
}
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_DEL_INCOMP;
// @@@ sample begin 9:1

class A {
public:
    A() : str_{std::make_unique<std::string>("sample")}
    {
        // @@@ ignore begin
        std::cout << __FILE__ ":" << __LINE__ << std::endl;
        // @@@ ignore end
    }

    ~A()
    {
        // @@@ ignore begin
        std::cout << __FILE__ ":" << __LINE__ << std::endl;
        // @@@ ignore end
    }

private:
    std::unique_ptr<std::string> str_;  // ~unique_ptr()は~A()から呼ばれる
};

class B;
// @@@ sample end

namespace {
TEST(ProgrammingConvention, delete_imcop)
{
    // @@@ sample begin 9:2

    void* v = new A;  // 暗黙の型変換
                      // これ自体は問題ないが、vをdeleteすると
                      // A::~A()が呼び出されないためメモリリークする

    B* b = static_cast<B*>(v);  // ダウンキャストの一種で、極めて悪質なことが多い
                                // 実際、このコードの中にクラスBの定義はないが
                                // このようなことができてしまう

#ifdef SANITIZER_LEAK  // @@@ delete
    delete v;          // このdeleleは、A::~A()を呼び出さない
#endif                 // @@@ delete
    // @@@ sample end

#ifndef SANITIZER_LEAK
    delete static_cast<A*>(v);
#endif
    IGNORE_UNUSED_VAR(b);
}
}  // namespace
SUPPRESS_WARN_END;
}  // namespace CastSample
