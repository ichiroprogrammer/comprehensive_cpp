#include <cassert>
#include <numeric>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace {
// @@@ sample begin 0:0

template <typename DST, typename SRC>
DST narrow_cast(SRC v)
{
    static_assert(std::is_integral_v<DST> && std::is_integral_v<DST>,
                  "DST, SRC shoud be integral-type.");
    auto r = static_cast<DST>(v);

    assert((r < 0) == (v < 0));        // 符号が変わっていないことの確認
    assert(static_cast<SRC>(r) == v);  // bit落ちしていないことの確認

    return r;
}
// @@@ sample end

TEST(ProgrammingConvention, NarrowCast)
{
    // clang-format off
    // @@@ sample begin 0:1

    auto ui32 = narrow_cast<uint32_t>(128);                // 安全なint32_t -> uint32_t
    ASSERT_EQ(ui32, 128);                                  //
    ASSERT_DEATH(ui32 = narrow_cast<uint32_t>(-128), "");  // 危険なint32_t -> uint32_t

    auto i8 = narrow_cast<int8_t>(127);                    // 安全なint32_t -> int8_t
    ASSERT_EQ(i8, 127);                                    //
    ASSERT_DEATH(i8 = narrow_cast<int8_t>(128), "");       // 危険なint32_t -> int8_t

    i8 = narrow_cast<int8_t>(-1);                          // 安全なint32_t -> int8_t
    ASSERT_EQ(i8, -1);                                     //
    ASSERT_DEATH(i8 = narrow_cast<int8_t>(-129), "");      // 危険なint32_t -> int8_t
    // @@@ sample end
    // clang-format on
}
}  // namespace

namespace ByteSample {
TEST(ProgrammingConvention, TypeByte)
{
    {
        // @@@ sample begin 1:0
        // uint8_tのビット演算例

        auto u    = uint8_t{0b1000'0001};
        auto ret0 = u << 1;
        // uint8_t ret1{u << 1};  // 縮小型変換のため、コンパイルエラー
        uint8_t ret1 = u << 1;

        static_assert(std::is_same_v<decltype(ret0), int>);  // u << 1はintになる
        ASSERT_EQ(0b1'0000'0010, ret0);
        ASSERT_EQ(0b0000'0010, ret1);
        // @@@ sample end
    }
    {
        // @@@ sample begin 1:1
        // uint8_tに代わりstd::byteを使用したビット演算例

        auto b    = std::byte{0b1000'0001};
        auto ret0 = b << 1;
        auto ret1 = std::byte{b << 1};

        static_assert(std::is_same_v<decltype(ret0), std::byte>);  // b << 1はstd::byteになる
        ASSERT_EQ(std::byte{0b0000'0010}, ret0);
        ASSERT_EQ(std::byte{0b0000'0010}, ret1);
        // @@@ sample end
    }
    {
        // @@@ sample begin 1:2

        std::byte b0{0b1000'0001};                           // OK
        auto      b1 = std::byte{0b1000'0001};               // OK
        std::byte b2 = static_cast<std::byte>(0b1000'0001);  // NG
        // std::byte b3 = 0b1000'0001;                       // NG コンパイルエラー
        // @@@ sample end
        IGNORE_UNUSED_VAR(b0, b1, b2);
    }
}
}  // namespace ByteSample

namespace BoolSample {
TEST(ProgrammingConvention, TypeBool)
{
    SUPPRESS_WARN_BEGIN;
    SUPPRESS_WARN_GCC_DEPRECATED;
    SUPPRESS_WARN_CLANG_DEPRECATED_INCREMENT_BOOL;
    // @@@ sample begin 2:0

#if __cplusplus < 201703L  // 以下のコードはC++14以前ではコンパイルできるが、
                           // C++17以降ではコンパイルエラー

    auto b = false;

    ASSERT_EQ(1, ++b);  // NG 予想通り動作するが、boolの目的外使用
    ASSERT_EQ(1, ++b);  // NG bは2ではなく1
    // ASSERT_EQ(1, --b);  // NG コンパイルエラー
#endif
    // @@@ sample end

    SUPPRESS_WARN_END;
}

// @@@ sample begin 2:1

void g(int32_t* ptr0, int32_t* ptr1) noexcept
{
    if (ptr0) {  // NG ポインタ型をbool値として使用
        return;
    }

    if (ptr1 == nullptr) {  // OK
        return;
    }

    // @@@ ignore begin
    // @@@ ignore end
}
// @@@ sample end

}  // namespace BoolSample

namespace EnumOldSample {
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_CLANG_ENUM_COMP_SWITCH;
// @@@ sample begin 3:0

enum CarLight { CL_Red, CL_Yellow, CL_Blue };
enum WalkerLight { WL_Red, WL_Yellow, WL_Blue };

bool f(CarLight cl) noexcept
{
    switch (cl) {
    // 非スコープドenumは下記のようなコードを許容する(if文でも同様)。
    // スコープドenumであればこのような間違いはコンパイルエラーで発見できる。
    case WL_Red:  // CL_Redの間違い?
        // @@@ ignore begin
        // @@@ ignore end
        break;
    case CL_Yellow:  // これは正しい
    case CL_Blue:
    default:
        // @@@ ignore begin
        // @@@ ignore end
        break;
    }

    // @@@ ignore begin
    return true;
    // @@@ ignore end
}
// @@@ sample end

SUPPRESS_WARN_END;

// @@@ sample begin 3:1

enum Colour {   // NG スコープドになっていない。
    Red   = 0,  // NG 配列インデックスでない場合、0を定義する必要はない。
    Green = 1,  // NG 連続値を定義する必要はない。
    Blue  = 2
};

// @@@ ignore begin
}  // namespace EnumOldSample
namespace EnumNewSample {
// @@@ ignore end

enum class Colour {  // OK
    Red,             // OK 不要な記述がない。
    Green,
    Blue
};
// @@@ sample end
}  // namespace EnumNewSample

namespace IndexEnumSample {
// @@@ sample begin 3:2

enum class Foo { FooA = 0, FooB, FooMAX };

struct Hoo  // structによるスコーピング
{
    enum {
        HooA = 0,  // OK
        HooB,      // OK 値は暗黙に定義
        HooMAX     // OK
    };
};

void f() noexcept
{
    // clang-format off
//  int32_t a0[Foo::FooMAX];                       // NG コンパイルエラー
    int32_t a1[static_cast<size_t>(Foo::FooMAX)];  // NG castが必要になる
    int32_t a2[Hoo::HooMAX];                       // OK
    // clang-format on
    // @@@ ignore begin

    IGNORE_UNUSED_VAR(a1, a2);
    // @@@ ignore end
}
// @@@ sample end
// @@@ sample begin 3:3

enum class IncompleteEnum;
enum class IncompleteEnum2 : uint64_t;

// このファイルから可視である範囲にIncompleteEnum、IncompleteEnum2の定義はないが、
// 前方宣言することで以下の関数宣言をすることができる。
extern void g(IncompleteEnum);
extern void g(IncompleteEnum2);
// @@@ sample end
}  // namespace IndexEnumSample

namespace StructSample {
// @@@ sample begin 4:0

struct Pod final {                        // NG finalは不要
    Pod()                     = default;  // OK
    ~Pod()                    = default;  // NG = defaultは不要
    Pod(Pod const&)           = delete;   // OK copyを禁止する場合
    Pod operator=(Pod const&) = delete;   // OK copyを禁止する場合

    int32_t x;
    int32_t y;
};
// @@@ sample end

// @@@ sample begin 4:1

typedef struct {  // NG   無名構造体
    int32_t x;
    int32_t y;
} StructNG;  // NG   無名構造体をtypedef

typedef struct StructOK_C_Share {  // Cとシェアする場合OK
    int32_t x;
    int32_t y;
} StructOK_C_Share;

struct StructOK {  // OK   Cとシェアしない場合このように書く
    int32_t x;
    int32_t y;
};
// @@@ sample end

}  // namespace StructSample

namespace UnionSample {
// @@@ sample begin 5:0

union XXX_REG {
    uint8_t  bytes[4];
    uint32_t word32;
};

uint8_t f() noexcept
{
    // 0x14000000はハードウェアレジスタのアドレスとする
    auto& XXX_REG_INST = *reinterpret_cast<XXX_REG*>(0x14000000);
    auto  byte_1       = XXX_REG_INST.bytes[1];

    return byte_1;
}
// @@@ sample end
}  // namespace UnionSample

namespace ArraySample {
void f() noexcept
{
    // @@@ sample begin 6:0

    // clang-format off
#if 0
    // g++では通常コンパイルエラーとなるが、-fpermissiveを付ければコンパイルできてしまう。
    char a[3]{"abc"};  // NG aはヌル終端されない
#else
    char a[]{"abc"};  // OK
#endif
    // clang-format on
    // @@@ sample end

    IGNORE_UNUSED_VAR(a);
}
}  // namespace ArraySample

namespace TypeAliasOldSample {
// @@@ sample begin 7:0

// C90スタイル
typedef unsigned int uint;                 // NG
typedef void (*void_func_int32)(int32_t);  // NG

// @@@ ignore begin
}  // namespace TypeAliasOldSample

namespace TypeAliasNewSample {

// @@@ ignore end

// C++11スタイル
using uint            = unsigned int;       // OK
using void_func_int32 = void (*)(int32_t);  // OK

template <class T>  // templateで型エイリアスを作ることもできる。
using Dict = std::map<std::string, T>;  // OK
// @@@ sample end

void f() noexcept
{
    // clang-format off
    // @@@ sample begin 7:1

    using pint32_t = int32_t*;  // pint32_tにはconstポインタを代入できない。

    pint32_t const pint32_0_c = nullptr;  // 一見pint32_0_cはconstポインタに見えるが。
    int32_t const* pint32_1_c = nullptr;

    // pint32_0_cの型とpint32_1_cの型が同じであれば問題ないのだが、
    // エイリアスのため結合順が変わった影響でそうはならない。
    // *pint32_0_cはconstではなく、pint32_0_cがconstとなる。
    static_assert(std::is_same_v<decltype(pint32_0_c),  int32_t* const>);
    static_assert(std::is_same_v<decltype(*pint32_0_c), int32_t&>);
    static_assert(std::is_same_v<decltype(pint32_1_c),  int32_t const*>);
    static_assert(std::is_same_v<decltype(*pint32_1_c), int32_t const&>);
    // @@@ sample end
    // clang-format on
    IGNORE_UNUSED_VAR(pint32_1_c);
}
}  // namespace TypeAliasNewSample

namespace PointerLiteral {
void f() noexcept
{
    // @@@ sample begin 8:0

    int32_t* a{0};        // NG   オールドスタイル
    int32_t* b{NULL};     // NG   C90の書き方
    int32_t* c{nullptr};  // OK   C++11
    // @@@ sample end

    IGNORE_UNUSED_VAR(a, b, c);
}

int g([[maybe_unused]] long a) noexcept { return 0; }

int g([[maybe_unused]] int* a) noexcept { return 1; }

TEST(ProgrammingConvention, call_with_null)
{
    SUPPRESS_WARN_BEGIN;
    SUPPRESS_WARN_CONV_NULL;

    // @@@ sample begin 8:1

    extern int g(long a) noexcept;
    extern int g(int* a) noexcept;

    // NULLを使ったことで、わかりづらいバグが発生する例
    g(NULL);  // NG NULLはポインタではないため、この呼び出しはg(long)を呼び出す
    static_assert(std::is_same_v<long, decltype(NULL)>);

    g(nullptr);  // OK 意図通り、g(int*)を呼び出す。
    static_assert(std::is_same_v<std::nullptr_t, decltype(nullptr)>);

    // @@@ sample end

    ASSERT_EQ(0, g(NULL));
    ASSERT_EQ(1, g(nullptr));
    SUPPRESS_WARN_END;
}

void g() noexcept
{
    {
        // @@@ sample begin 8:2

        auto a = 123'456'789U;       // = 123456789
        auto b = 0x123'456'789U;     // = 0x123456789
        auto c = 0b1001'0001'0101U;  // = 0x915
        // @@@ sample end
        ASSERT_EQ(a, 123456789U);
        ASSERT_EQ(b, 0x123456789U);
        ASSERT_EQ(c, 0x915U);
    }
    {
        // @@@ sample begin 8:3

        bool a{0};          // NG
        bool b{!0};         // NG
        bool c{false};      // OK
        auto d = bool{0};   // NG
        auto e = bool{!0};  // NG
        auto f = true;      // OK
        // @@@ sample end

        IGNORE_UNUSED_VAR(a, b, c, d, e, f);
    }
    {
        // @@@ sample begin 8:4

        auto a = 432l;  // NG 4321と区別が難しい
        auto b = 432L;  // OK
        // @@@ sample end
        IGNORE_UNUSED_VAR(a, b);
    }
}
}  // namespace PointerLiteral

namespace AutoDeclTypeSample {

std::string get_name() { return ""; }

// @@@ sample begin 9:0

void f(std::vector<std::string> const& strs)
{
    auto s0 = std::string{"hehe"};  // OK
    auto s1{std::string{"hehe"}};   // OKだが、通常は代入を使用する
    auto s2 = s0;                   // OK
    auto s3 = get_name();           // NG get_name()の戻り値を見ないとs3の型が不明

    for (auto const& str : strs) {  // OK strsの型が明らかであるため、strの型も明らか
        // @@@ ignore begin
        IGNORE_UNUSED_VAR(str);
        // @@@ ignore end
    }
}
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_GCC_LOCAL_RETURN;
SUPPRESS_WARN_CLANG_RETURN_STACK_ADDRESS;
// @@@ sample begin 9:1

class A {
public:
    A() = default;

#if 0  // NG この関数を呼び出すとクラッシュ
    std::string const& Get(char first_byte) const noexcept
    {
        static std::string const empty;
        // clang-format off
        for (auto const str : strs) {       // NG &の付け忘れのため、スタック上の
            if (str.at(0) == first_byte) {  //    オブジェクトのリファレンスをreturnする。
                return str;
            }
        }
        // clang-format on
        return empty;
    }

#else  // OK 上のGetの修正。
    std::string const& Get(char first_byte) const noexcept
    {
        static std::string const empty;
        // clang-format off
        for (auto const& str : strs) {      // OK &を付けて、インスタンスのオブジェクトの
            if (str.at(0) == first_byte) {  //    リファレンスを返せるようになった。
                return str;
            }
        }
        // clang-format on
        return empty;
    }
#endif

private:
    std::vector<std::string> strs{"aha", "ihi", "uhu"};
};
// @@@ sample end
SUPPRESS_WARN_END;

TEST(ProgrammingConvention, auto_ref)
{
    auto a = A{};

    ASSERT_EQ("aha", a.Get('a'));
    ASSERT_EQ("", a.Get('A'));
}

void g0() noexcept
{
    // @@@ sample begin 9:2

    auto a = 1;       // OK aの型はint
    auto b(1);        // 別の規制でNG ()より{}を優先的に使うべき
    auto c{1};        // OK cの型はint
    auto d = {1};     // NG dの型はstd::initializer_list<int>
    auto e = {1, 2};  // NG eの型はstd::initializer_list<int>
    auto f = std::initializer_list<int>{1, 2};  // OK

    static_assert(std::is_same_v<decltype(a), int>, "type not same");
    static_assert(std::is_same_v<decltype(b), int>, "type not same");
    static_assert(std::is_same_v<decltype(c), int>, "type not same");
    static_assert(std::is_same_v<decltype(d), std::initializer_list<int>>, "type not same");
    static_assert(std::is_same_v<decltype(e), std::initializer_list<int>>, "type not same");
    static_assert(std::is_same_v<decltype(f), std::initializer_list<int>>, "type not same");
    // @@@ sample end

    IGNORE_UNUSED_VAR(d, e, f);
}

void g1() noexcept
{
    // @@@ sample begin 9:3

    short  s0{0};
    short& s0_ref{s0};

    {  // autoとdecltypeが同じ動作をするパターン
        auto a = s0;
        static_assert(std::is_same_v<decltype(a), short>);

        decltype(s0) d = s0;
        static_assert(std::is_same_v<decltype(d), short>);

        decltype(auto) da = s0;
        static_assert(std::is_same_v<decltype(da), short>);
        ASSERT_EQ(a, s0);   // @@@ delete
        ASSERT_EQ(d, s0);   // @@@ delete
        ASSERT_EQ(da, s0);  // @@@ delete
    }
    {  // autoとdecltypeに違いが出るパターン
        auto a = s0_ref;
        static_assert(std::is_same_v<decltype(a), short>);

        decltype(s0_ref) d = s0_ref;  // dはリファレンス
        static_assert(std::is_same_v<decltype(d), short&>);

        decltype(auto) da = s0_ref;  // daはリファレンス
        static_assert(std::is_same_v<decltype(da), short&>);
        ASSERT_EQ(a, s0);   // @@@ delete
        ASSERT_EQ(d, s0);   // @@@ delete
        ASSERT_EQ(da, s0);  // @@@ delete
    }

    short s1{0};
    {  // 微妙な違いで出るパターン
        auto a = s0 + s1;
        static_assert(std::is_same_v<decltype(a), int>);

        decltype(s0) d = s0 + s1;  // これが意図的ならよいが
        static_assert(std::is_same_v<decltype(d), short>);

        decltype(s0 + s1) d2 = s0 + s1;  // int&&にはならない
        static_assert(std::is_same_v<decltype(d2), int>);

        decltype(auto) da = s0 + s1;  // この方がクローンがないため上よりも良い
        static_assert(std::is_same_v<decltype(da), int>);
        ASSERT_EQ(a, s0 + s1);   // @@@ delete
        ASSERT_EQ(d, s0);        // @@@ delete
        ASSERT_EQ(d2, s0 + s1);  // @@@ delete
        ASSERT_EQ(da, s0 + s1);  // @@@ delete
    }
    // @@@ sample end
}
}  // namespace AutoDeclTypeSample

namespace InitializationSample {
void f() noexcept
{
    // @@@ sample begin 11:0

    int32_t a0(0);            // NG
    int32_t a1 = 0;           // NG
    int32_t a2{0};            // OK 一様初期化
    int32_t a3 = {0};         // NG 代入演算子を伴う一様初期化
    auto    a4 = 0;           // OK AAAの場合は一様初期を使わなくても問題ない
    auto    a5 = int32_t{0};  // OK AAA且つ一様初期
    // @@@ sample end
    // @@@ sample begin 11:1

    int32_t& r0(a0);     // NG
    int32_t& r1 = a0;    // OK
    int32_t& r2{a0};     // OK 一様初期化
    int32_t& r3 = {a0};  // NG 代入演算子を伴う一様初期化
    auto&    r4 = a0;  // OK AAAの場合は一様初期を使わなくても問題ないが、&の付け忘れに気を付ける

    int32_t* p0(&a0);     // NG
    int32_t* p1 = &a0;    // OK
    int32_t* p2{&a0};     // OK 一様初期化
    int32_t* p3 = {&a0};  // NG 代入演算子を伴う一様初期化
    auto     p4 = &a0;    // OK AAAの場合は一様初期を使わなくても問題ない
    auto*    p5 = &a0;    // OK AAAの場合は一様初期を使わなくても問題ない
    // @@@ sample end

    IGNORE_UNUSED_VAR(a0, a1, a2, a3, a4, a5);
    IGNORE_UNUSED_VAR(r0, r1, r2, r3, r4, p0, p1, p2, p3, p4, p5);

    static_assert(std::is_same_v<int32_t&, decltype(r4)>);
    static_assert(std::is_same_v<int32_t*, decltype(p4)>);
    static_assert(std::is_same_v<int32_t*, decltype(p5)>);
}

class Widget {};

TEST(ProgrammingConvention, class_init)
{
    // @@@ sample begin 11:2

    // 構造体の初期化
    struct Struct {
        int32_t     a;
        char const* str;
    };

    Struct s0{1, "1"};           // OK 代入演算子を伴わない一様初期化
    Struct s1 = {2, "2"};        // NG 代入演算子による一様初期化
    Struct s2{};                 // OK s2.aは0、s2.strはnullptrに初期化される。
    Struct s3;                   // NG s3は未初期化
    auto   s4 = Struct{1, "1"};  // OK AAAスタイル
    auto   s5 = Struct{};        // OK AAAスタイル
    IGNORE_UNUSED_VAR(s0, s1, s2, s3, s4, s5);  // @@@ delete

    // クラスの初期化
    std::unique_ptr<Widget> a{std::make_unique<Widget>()};   // OK
    std::unique_ptr<Widget> b(std::make_unique<Widget>());   // NG {}を使うべき
    auto                    c{std::make_unique<Widget>()};   // OK
    auto                    d = std::make_unique<Widget>();  // OK
    // このような場合、重複を避けるため、変数宣言の型はautoが良い

    // std::string、std::string_viewの初期化
    std::string str0{"222"};     // OK
    std::string str1 = {"222"};  // NG = は不要
    std::string str2("222");     // NG {}で初期化できない時のみ、()を使う。
    std::string str3(3, '2');    // OK {}では初期化できない。str3 == "222"
    std::string str4 = "222";    // OK 例外的に認める
    auto        str5 = std::string{"222"};  // OK AAAスタイル

    std::string_view sv0 = "222";                    // OK 例外的に認める
    auto             sv1 = std::string_view{"222"};  // OK AAAスタイル
    ASSERT_EQ("222", str0);                          // @@@ delete
    ASSERT_EQ(str1, str2);                           // @@@ delete
    ASSERT_EQ(str2, str3);                           // @@@ delete
    ASSERT_EQ(str3, str4);                           // @@@ delete
    ASSERT_EQ(str4, str5);                           // @@@ delete
    ASSERT_EQ(str4, sv0);                            // @@@ delete
    ASSERT_EQ(str4, sv1);                            // @@@ delete

    // {}、()による初期化の違い
    std::vector<int32_t> vec0_i{1, 2, 3};  // OK vec0_i.size() == 3 && vec0_i[0] == 1 ...
    std::vector<int32_t> vec1_i{10};       // OK vec1_i.size() == 1 && vec1_i[0] == 10
    std::vector<int32_t> vec2_i(10);       // OK vec1_i.size() == 10
    auto                 vec3_i = std::vector{1, 2, 3};  // OK vec0_iと同じ

    std::vector<std::string> vec1_s{10};  // OK vec1_s.size() == 10
    std::vector<std::string> vec2_s(10);  // NG vec2_s.size() == 10  {}を優先するべき
    auto                     vec3_s = std::vector<std::string>{10};  // OK vec1_sと同じ

    // vec1_i、vec2_i、vec1_sの初期化は似ているが、結果は全く異なる。
    // vec1_iは、vector(initializer_list<>)を呼び出す。
    // vec2_iは、vector(int)を呼び出す。
    // vec1_sは、vector(int)を呼び出す。

    ASSERT_EQ(3, vec0_i.size());
    ASSERT_EQ(1, vec1_i.size());
    ASSERT_EQ(10, vec2_i.size());
    ASSERT_EQ(vec0_i, vec3_i);
    ASSERT_EQ(10, vec1_s.size());  // vec1_iと同じ形式で初期化したが結果は全く異なる。
    ASSERT_EQ(10, vec2_s.size());
    ASSERT_EQ(10, vec3_s.size());
    // @@@ sample end
}

TEST(ProgrammingConvention, decltype_init)
{
    // @@@ sample begin 11:3

    auto  a = 0;
    auto& b = a;

    decltype(a)    c = a;    // OKがautoの方が良い
    decltype(a)    d = {a};  // NG
    decltype(b)    e = a;    // OK
    decltype(auto) f = b;    // OK

    static_assert(std::is_same_v<decltype(c), int>);
    static_assert(std::is_same_v<decltype(d), int>);
    static_assert(std::is_same_v<decltype(e), int&>);
    static_assert(std::is_same_v<decltype(f), int&>);
    // @@@ sample end
    IGNORE_UNUSED_VAR(a, b, c, d, e, f);
}

SUPPRESS_WARN_GCC_BEGIN;
SUPPRESS_WARN_GCC_NOT_EFF_CPP;

TEST(ProgrammingConvention, ArrayInit)
{
    // @@@ sample begin 11:4

    int32_t array0[3]{1, 2, 3};     // OK 代入演算子を伴わない一様初期化
    int32_t array1[3] = {1, 2, 3};  // NG 代入演算子による一様初期化
    int32_t array2[3]{};            // OK 代入演算子を伴わない一様初期化
    int32_t array3[3] = {};         // NG 代入演算子による一様初期化

    char c_str0[]{'1', '2', '\0'};     // OKだが、非推奨
    char c_str1[] = {'1', '2', '\0'};  // NG 代入演算子による一様初期化
    char c_str2[] = {"12"};            // NG 代入演算子による一様初期化
    char c_str3[]{"12"};               // OK
    char c_str4[] = "12";              // OK
    // @@@ sample end

    IGNORE_UNUSED_VAR(array0, array1, array2, array3);
    ASSERT_STREQ(c_str0, c_str1);
    ASSERT_STREQ(c_str2, c_str3);
    ASSERT_STREQ(c_str2, c_str4);
}
SUPPRESS_WARN_GCC_END;

TEST(ProgrammingConvention, var_initialization)
{
    // @@@ sample begin 11:5

    int32_t*       ptr1 = nullptr;  // OK
    int32_t*       ptr2{nullptr};   // OK
    char const*    pchar0 = 0;      // NG
    char*          pchar1 = NULL;   // NG
    int32_t const* ptr0(nullptr);   // NG {}か=で初期化する
    // @@@ sample end

    IGNORE_UNUSED_VAR(ptr0, ptr1, ptr2, pchar0, pchar1);
}

// @@@ sample begin 11:6

constexpr int32_t f_constexpr(int32_t a) noexcept { return a * 3; }
int32_t           f_normal(int32_t a) noexcept { return a * 3; }
// @@@ sample end

TEST(ProgrammingConvention, constexpr_usage)
{
    // @@@ sample begin 11:7

    constexpr auto a = f_constexpr(3);  // OK
    auto const     b = f_constexpr(3);  // NG constexprにできる
    // constexpr auto c = f_normal(3);  // NG コンパイルエラー
    auto const d = f_normal(3);  // OK

    // @@@ sample end
    IGNORE_UNUSED_VAR(a, b, d);
}

TEST(ProgrammingConvention, const_object_inited_by_lambda)
{
    // @@@ sample begin 11:8

    int32_t len{10};  // ここではlenは固定だが、関数引数等で外部から与えられるとする

    auto vc0 = std::vector<int32_t>(len);  // vc0が初期化以外で変更されないのであれば、NG
    std::iota(vc0.begin(), vc0.end(), 1);  // vc0の初期化

    auto const vc1 = [len]() {  // OK vc1の初期化
        std::vector<int32_t> ret(len);
        std::iota(ret.begin(), ret.end(), 1);
        return ret;
    }();  // ラムダ式の生成と呼び出し
    // @@@ sample end

    ASSERT_EQ((std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), vc0);
    ASSERT_EQ((std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), vc1);
    static_assert(std::is_same_v<std::vector<int32_t> const, decltype(vc1)>);
}

}  // namespace InitializationSample

namespace RvalueBind {
#define SANITIZER_NG 1

#if SANITIZER_NG == 1
#define rvalue_bind_Opt DISABLED_rvalue_bind
#else
#define rvalue_bind_Opt rvalue_bind
#endif
TEST(ProgrammingConvention, rvalue_bind_Opt)
{
#if !defined(__clang_analyzer__)  // ドキュメントの都合上、scan-buildで指摘されたくない
    SUPPRESS_WARN_BEGIN;
    SUPPRESS_WARN_CLANG_DANGLING_GSL
    // @@@ sample begin 12:0

    char const* str = std::string{"str"}.c_str();
    // strが指すポインタはこの行では解放済

    ASSERT_STREQ(str, "str");  //    strは無効なポインタを保持であるため、未定義動作
    // @@@ sample end
    SUPPRESS_WARN_END;
#endif
}
}  // namespace RvalueBind
