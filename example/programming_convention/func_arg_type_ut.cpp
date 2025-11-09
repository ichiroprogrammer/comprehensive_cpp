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

namespace ArgumentSample2 {

// @@@ sample begin 0:1

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
// @@@ sample begin 0:2

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

// @@@ sample begin 0:3

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

// @@@ sample begin 1:0

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
    // @@@ sample begin 1:1

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

// @@@ sample begin 1:2

// ポインタではなく、配列へのリファレンスを使用することで、
// 上記のようなバグを避けることができる

std::vector<std::string> f_ref_2(Base const (&array)[2])  // OK 配列へのリファレンス
{
    auto ret = std::vector<std::string>{array_length(array)};

    // arrayの型はポインタではなく、リファレンスなのでstd::endが使える
    std::transform(array, std::end(array), ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

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

template <typename T, size_t N>                                // std::arrayの第2パラメータの型はsize_t
std::vector<std::string> h_ref(std::array<T, N> const& array)  // OK std::arrayへのリファレンス
{
    auto ret = std::vector<std::string>{N};

    std::transform(std::begin(array), std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

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

    std::transform(*array, std::end(*array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

    return ret;
}
// @@@ sample end

namespace {

TEST(ProgrammingConvention, not_use_convert_to_ptr)
{
    // @@@ sample begin 1:3

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
// @@@ sample begin 2:0

int32_t default_arg{0};
int32_t get_default_arg(int32_t a = default_arg) noexcept { return a; }
// @@@ sample end

TEST(ProgrammingConvention, call_get_default_arg)
{
    // @@@ sample begin 2:1

    ASSERT_EQ(0, get_default_arg());  // default_arg == 0

    default_arg = 2;

    ASSERT_EQ(2, get_default_arg());  // default_arg == 2
    // @@@ sample end
}
}  // namespace ArgumentSample2

namespace {

// @@@ sample begin 3:0

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
    IGNORE_UNUSED_VAR(str);  // @@@ delete
}
// @@@ sample end

TEST(ProgrammingConvention, use_convert_to_ptr)
{
    // @@@ sample begin 3:1

    auto s = std::make_unique<std::string>("hehe");

    f0(s);   // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f1(*s);  // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f2(*s);  // sも、sが指しているstd::stringオブジェクトも変更されない
    // @@@ sample end
}
}  // namespace
