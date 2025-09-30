#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>

#include "gtest_wrapper.h"

#include "scope2.h"
#include "suppress_warning.h"

#if 0
#include "scope.h"
#endif

namespace ScopeSample {
// @@@ sample begin 0:0

uint32_t xxx;  // NG 外部から参照可能な静的変数
uint32_t yyy;  // NG 同上

uint32_t f(uint32_t yyy) noexcept
{
    auto xxx = 0;  // NG 関数外xxxと関数内xxxのスコープが重なっており区別が付きづらい

    return xxx + yyy;
}
// なお、
//  scope.h内では、  uint64_t yyy;
//  scope.cpp内では、uint32_t yyy;
//  となっており、宣言と定義が矛盾している。
//  この問題は、このファイルからscope.hをインクルードすれば防げる。
// @@@ sample end

TEST(ProgrammingConvention, Inner)
{
    {
        constexpr auto fs = StaticString<4>{"abc"};

        static_assert(sizeof(4) == fs.Size());
        ASSERT_STREQ("abc", fs.String());
    }
    {
        const auto fs = StaticString<4>{'a', 'b', 'c'};

        static_assert(sizeof(4) == fs.Size());
        ASSERT_STREQ("abc", fs.String());
    }
}

TEST(ProgrammingConvention, using_import)
{
    {
        // @@@ sample begin 1:0

        using std::string;         // NG この関数内でのstd::stringの使用箇所が少ないのであれば、
                                   //    using宣言ではなく、名前修飾する
        auto s_0 = string{"str"};  // NG
        auto s_1 = std::string{"str"};  // OK

        // 大量のstd::stringリテラルを使用する場合
        using std::literals::string_literals::operator""s;  // OK

        auto s_2 = "str"s;  // OK
        // ...
        auto s_N = "str"s;  // OK

        // クラス内でのusing宣言
        struct Base {
            void f(){};
        };

        struct Derived : Base {
            using Base::Base;  // OK 継承コンストラクタ
            using Base::f;     // OK B::fのインポート
            void f(int){};
        };
        // @@@ sample end
        IGNORE_UNUSED_VAR(s_0, s_1, s_2, s_N);
    }

    {
        // @@@ sample begin 1:1

        using namespace std;  // NG

        auto s0 = string{"str"};

        auto s1 = std::literals::string_literals::operator""s("str", 3);  // NG
        static_assert(std::is_same_v<std::string, decltype(s1)>);

        using namespace std::literals::string_literals;  // OK 例外的にOK

        auto s2 = "str"s;
        static_assert(std::is_same_v<std::string, decltype(s2)>);
        // @@@ sample end

        ASSERT_EQ(s0, s1);
        ASSERT_EQ(s0, s2);
    }
}
}  // namespace ScopeSample

namespace NamespaceInlineSample {
// @@@ sample begin 1:2

namespace XxxLib {
namespace OldVersion {
int32_t f() noexcept
{
    // @@@ ignore begin
    return 2;
    // @@@ ignore end
}
}  // namespace OldVersion

inline namespace NewVersion {  // NG inline
int32_t f() noexcept
{
    // @@@ ignore begin
    return 3;
    // @@@ ignore end
}
}  // namespace NewVersion

int32_t g() noexcept
{
    return f();  // NG NewVersion::f()が呼ばれる。
}
// @@@ sample end

namespace {
TEST(ProgrammingConvention, inline_namespace) { ASSERT_EQ(3, g()); }
}  // namespace

}  // namespace XxxLib

#define SHIP_TO_JAPAN

// @@@ sample begin 1:3
// 例外的にOKな例

#if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK
#define INLINE_JAPAN inline                                                 // OK
#define INLINE_US
#define INLINE_EU

#elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK
#define INLINE_JAPAN
#define INLINE_US inline  // OK
#define INLINE_EU

#elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // OK
#define INLINE_JAPAN
#define INLINE_US
#define INLINE_EU inline  // OK

#else
static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
#endif

namespace Shipping {
INLINE_JAPAN namespace Japan  // OK
{
    int32_t DoSomething() { return 0; }
}

INLINE_US namespace US  // OK
{
    int32_t DoSomething() { return 1; }
}

INLINE_EU namespace EU  // OK
{
    int32_t DoSomething() { return 2; }
}
}  // namespace Shipping
// @@@ sample end

TEST(ProgrammingConvention, inline_namespace2)
{
    // @@@ sample begin 1:4

    // SHIP_TO_JAPAN/US/EUを切り替えることで、対応したDoSomethingが呼ばれる
    // この例ではSHIP_TO_JAPANが定義されているため、Shipping::Japan::DoSomethingが呼ばれる
    ASSERT_EQ(0, Shipping::DoSomething());

    // 名前修飾することで、すべてのDoSomethingにアクセスできるため、単体テストも容易
    ASSERT_EQ(0, Shipping::Japan::DoSomething());
    ASSERT_EQ(1, Shipping::US::DoSomething());
    ASSERT_EQ(2, Shipping::EU::DoSomething());
    // @@@ sample end
}

}  // namespace NamespaceInlineSample

namespace NamenameADL {
// ADLの副作用
// @@@ sample begin 2:0

namespace NS_0 {
class X {};

std::string f(X, int32_t)  // 第2引数int32_t
{
    return "in NS_0";
}
}  // namespace NS_0

namespace NS_1 {

std::string f(NS_0::X, uint32_t)  // 第2引数uint32_t
{
    return "in NS_1";
}

TEST(ProgrammingConvention, adl)
{
    // in NS_1
    // 下記関数fの探索名前空間には、
    //  * 第1引数の名前空間がNS_0であるため、ADLにより、
    //  * この関数の宣言がNS_1で行われているため、
    // NS_0、NS_1が含まれる。
    // これにより、下記fの候補は、NS_0::f、NS_1::fになるが、第2引数1がint32_t型であるため、
    // 下記は、NS_0::fの呼び出しになる。

    ASSERT_EQ("in NS_0", f(NS_0::X(), 1));  // NS_0::fが呼ばれる。

    ASSERT_EQ("in NS_1", NS_1::f(NS_0::X(), 1));  // NS_1::fの呼び出しには名前修飾が必要
}
}  // namespace NS_1
// @@@ sample end
}  // namespace NamenameADL

namespace NamenameAliasSample {

// @@@ sample begin 3:0

std::vector<std::string> find_files_recursively(std::string const&                                path,
                                                std::function<bool(std::filesystem::path const&)> condition)
{
    namespace fs = std::filesystem;  // OK 長い名前を短く

    auto files  = std::vector<std::string>{};
    auto parent = fs::path{path.c_str()};

    using namespace fs;  // NG エイリアスをusing namespaceで使用しない

    std::for_each(fs::recursive_directory_iterator{parent},  // OK namespaceエイリアス
                  fs::recursive_directory_iterator{},        // OK namespaceエイリアス
                  // @@@ ignore begin
                  [&](fs::path const& p) {
                      if (condition(p)) {
                          files.emplace_back(p.generic_string());
                      }
                  }
                  // @@@ ignore end
    );

    using fs::recursive_directory_iterator;  // NG エイリアスをusing宣言で使用しない

    std::for_each(recursive_directory_iterator{parent},  // NG
                  recursive_directory_iterator{},        // NG
                  // @@@ ignore begin
                  [&](fs::path const& p) {
                      if (condition(p)) {
                          files.emplace_back(p.generic_string());
                      }
                  }
                  // @@@ ignore end
    );

    return files;
}
// @@@ sample end
}  // namespace NamenameAliasSample
