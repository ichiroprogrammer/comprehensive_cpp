#include <cstdint>
#include <iostream>

#include "gtest_wrapper.h"

#include "measure_performance.h"
#include "suppress_warning.h"

namespace OperatorIncExample {

SUPPRESS_WARN_CLANG_BEGIN;
SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;

// @@@ sample begin 0:0

class A {
public:
    A& operator++() noexcept  // 前置++
    {
        ++a_;  // メンバ変数のインクリメント
        return *this;
    }

    A operator++(int) noexcept  // 後置++
    {
        A old{*this};  // リターンするためのオブジェクト
        ++(*this);     // 前置++
        return old;    // oldオブジェクトのリターン(オブジェクトのコピー)
    }

    operator int() const noexcept { return a_; }

private:
    int32_t a_{0};
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, inc_pre_post)
{
    // @@@ sample begin 0:1

    constexpr auto count = 10000000U;

    auto a_post = A{};
    auto post   = MeasurePerformance(count, [&a_post] {
        a_post++;  // NG 効率が悪い
    });

    auto a_pre = A{};
    auto pre   = MeasurePerformance(count, [&a_pre] {
        ++a_pre;  // OK 上記に比べると効率が良い
    });

    ASSERT_GT(post, pre);  // 前置++の処理は後置++より効率が良い

    std::cout << "pre :" << pre.count() << " msec" << std::endl;
    std::cout << "post:" << post.count() << " msec" << std::endl;

    // 私の環境では以下のような出力が得られた
    // pre :24 msec
    // post:37 msec
    // @@@ sample end

    ASSERT_EQ(count, a_post);
    ASSERT_EQ(count, a_pre);
}
}  // namespace
}  // namespace OperatorIncExample

namespace OperatorPlusExample {
// @@@ sample begin 1:0

class A {
public:
    explicit A(int32_t a) noexcept : a_{a} {}

    A& operator+=(A const& rhs) noexcept
    {
        a_ += rhs.a_;
        return *this;
    }
    // @@@ ignore begin

    int32_t Value() const noexcept { return a_; }

private:
    int32_t a_{0};
    int32_t array_[100000]{};  // 前置と後置の差をわかり易くするためにあえて巨大なエリアを定義

    // @@@ ignore end
    friend A operator+(A const& lhs, A const& rhs) noexcept  // メンバ関数に見えるが、非メンバ関数
    {
        A tmp{lhs};  // operator +=に対して、
        tmp += rhs;  // 「tmpを作り、それを返す]をしなければならない。
        return tmp;
    }
};

// @@@ sample end
TEST(ProgrammingConvention, op_plus)
{
    // @@@ sample begin 1:1

    auto a = A{1};
    auto b = A{2};

    a = a + b;  // NG 無駄なコピーが発生する
    ASSERT_EQ(a.Value(), 3);

    a += b;  // OK 無駄なコピーが発生しない
    ASSERT_EQ(a.Value(), 5);
    // @@@ sample end
}
}  // namespace OperatorPlusExample

namespace ReturnObjectSample {

// @@@ sample begin 2:0

struct HugeClass {
    int32_t a{0};
    int32_t array[100000]{};
};

HugeClass f() noexcept  // NG 巨大なオブジェクトのリターン
{
    auto obj = HugeClass{};

    // @@@ ignore begin
    // @@@ ignore end

    return obj;  // RVOが使えない場合パフォーマンス問題を引き起こす可能性がある。
}

class A {
public:
    // RVO、SSOをサポートしているコンパイラを使用している場合、下記の2つのGetNameの
    // パフォーマンスに大差はない(ほとんどのC++コンパイラはRVO、SSOをサポートしている)。
    // 使い勝手は、std::string GetName()の方が良い。
    static std::string GetName()  // OK この程度なら問題はない
    {
        return "sample";
    }

    static void GetName(std::string& s)  // OK
    {
        s = "sample";
    }
};
// @@@ sample end
SUPPRESS_WARN_CLANG_END;

// @@@ sample begin 3:0

std::string MakeString(int a, int b)
{
    auto ret = std::string{};

    // @@@ ignore begin
    ret += std::to_string(a + b);
    // @@@ ignore end
    // 文字列操作
    // @@@ ignore begin
    // @@@ ignore end

#if 0
    // NG
    // std::moveのため、RVOが抑止される。
    // -Wpessimizing-moveを指定してg++/clang++でコンパイルすれば、
    // "moving a local object in a return statement prevents copy elision"
    // という警告が出る。

    return std::move(ret);
#else
    // OK
    // ローカルオブジェクトには通常RVOが行われるため、std::moveするよりも無駄が少ない。

    return ret;
#endif
}
// @@@ sample end

}  // namespace ReturnObjectSample

namespace String_StringRef_StringView {

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_PARAM;
// clang-format off
// @@@ sample begin 4:0
// テスト０用関数

void f0(std::string const& str) { /* strを使用した何らかの処理 */ }
void f1(std::string str)        { /* strを使用した何らかの処理 */ }
void f2(std::string_view str)   { /* strを使用した何らかの処理 */ }
// @@@ sample end
// clang-format on
SUPPRESS_WARN_END;

namespace {
TEST(ProgrammingConvention, string_string_ref_string_view_0)
{
    // @@@ sample begin 4:1
    // テスト０―０

    auto str     = std::string{__func__};
    auto f0_msec = MeasurePerformance(10000000, [&str] { f0(str); });
    auto f1_msec = MeasurePerformance(10000000, [&str] { f1(str); });
    auto f2_msec = MeasurePerformance(10000000, [&str] { f2(str); });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // f0 : 50 msec
    // f1 :222 msec
    // f2 : 55 msec
    // つまり、f0 < f2 < f1であり、f0とf2は大差がなく、f1は極めて非効率である。
    // 従って、文字列リテラルを関数に渡す場合の引数の型は、
    // std::string const&か、std::string_viewとするのが効率的である。
    // @@@ sample end

    std::cout << "f0 :" << f0_msec.count() << std::endl;
    std::cout << "f1 :" << f1_msec.count() << std::endl;
    std::cout << "f2 :" << f2_msec.count() << std::endl;
}

TEST(ProgrammingConvention, string_string_ref_string_view_1)
{
    // @@@ sample begin 4:2
    // テスト０―１

    auto f0_msec = MeasurePerformance(10000000, [] { f0(__func__); });
    auto f1_msec = MeasurePerformance(10000000, [] { f1(__func__); });
    auto f2_msec = MeasurePerformance(10000000, [] { f2(__func__); });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // f0 :674 msec
    // f1 :662 msec
    // f2 :115 msec
    // つまり、f2 < f1 < f0であり、f0、f1は極めて非効率である。
    // 従って、文字列を関数に渡す場合の引数の型は、std::string_viewとするのが効率的である。
    //
    // テスト０―０、テスト０―１の結果から、
    //   * 文字列リテラルからstd::string型テンポラリオブジェクトを作るような呼び出しが多い場合、
    //     std::string_view
    //   * 上記のような呼び出しがほとんどない場合、std::string const&
    // を引数型とすべきである。
    // 使用方法が想定できない場合、極めて非効率なテスト０－１のf0のパターンを避けるため、
    // std::string_viewを選択すべきだろう。
    // @@@ sample end

    std::cout << "f0 :" << f0_msec.count() << std::endl;
    std::cout << "f1 :" << f1_msec.count() << std::endl;
    std::cout << "f2 :" << f2_msec.count() << std::endl;
}
}  // namespace

// @@@ sample begin 4:3
// テスト１用クラス

class A0 {
public:
    A0(std::string const& str) : str_{str} {}

private:
    std::string str_;
};

class A1 {
public:
    A1(std::string str) : str_{std::move(str)} {}  // strの一時オブジェクトをmoveで利用

private:
    std::string str_;
};

class A2 {
public:
    A2(std::string_view str) : str_{str} {}

private:
    std::string str_;
};
// @@@ sample end

namespace {
TEST(ProgrammingConvention, string_string_ref_string_view_2)
{
    // @@@ sample begin 4:4
    // テスト１―０

    auto str     = std::string{__func__};
    auto a0_msec = MeasurePerformance(10000000, [&str] { A0 a{str}; });
    auto a1_msec = MeasurePerformance(10000000, [&str] { A1 a{str}; });
    auto a2_msec = MeasurePerformance(10000000, [&str] { A2 a{str}; });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // A0 :258 msec
    // A1 :314 msec
    // A2 :683 msec
    // つまり、A0 < A1 < A2であり、A0とA1は大差がなく、A2は極めて非効率である。
    // 従って、stringオブジェクトを関数に渡す場合の引数の型は、
    // std::string const&か、std::stringとするのが効率的である。
    // @@@ sample end

    std::cout << "A0 :" << a0_msec.count() << std::endl;
    std::cout << "A1 :" << a1_msec.count() << std::endl;
    std::cout << "A2 :" << a2_msec.count() << std::endl;
}

TEST(ProgrammingConvention, string_string_ref_string_view_3)
{
    // @@@ sample begin 4:4
    // テスト１―１

    auto a0_msec = MeasurePerformance(10000000, [] { A0 a{__func__}; });
    auto a1_msec = MeasurePerformance(10000000, [] { A1 a{__func__}; });
    auto a2_msec = MeasurePerformance(10000000, [] { A2 a{__func__}; });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // A0 :834 msec
    // A1 :774 msec
    // A2 :704 msec
    // つまり、A2 < A1 < A0であり、A0の効率がやや悪い。
    // 従って、文字列リテラルを関数に渡す場合の引数の型は、
    // std::stringか、std::string_viewとするのが効率的である。
    //
    // コンストラクタのインターフェースとしては、
    // 実引数オブジェクトのライフタイムを考慮しなくて良いため、A0よりもA1の方が優れている。
    // この観点と、テスト１－０、テスト１－１の結果を総合的に考えれば、
    // このような場合の引数の型は、std::stringを選択すべきだろう。
    // @@@ sample end

    std::cout << "A0 :" << a0_msec.count() << std::endl;
    std::cout << "A1 :" << a1_msec.count() << std::endl;
    std::cout << "A2 :" << a2_msec.count() << std::endl;
}
}  // namespace
}  // namespace String_StringRef_StringView
