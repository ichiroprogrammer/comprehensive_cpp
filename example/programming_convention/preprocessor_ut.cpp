#include <cstdint>
#include <iostream>
#include <string>

#include "gtest_wrapper.h"

#include "preprocessor.h"
#include "suppress_warning.h"

namespace PreprocessorSample {

#define DEBUG

// @@@ sample begin 0:0

bool f() noexcept
{
#ifdef DEBUG  // NG
    std::cout << __func__ << ":" << __LINE__ << std::endl;
#endif

    // @@@ ignore begin
    // @@@ ignore end

#if 0  // NG
    return true;
#else  // NG
    return false;
#endif
}

// やむを得ず条件付きコンパイルが必要な場合、下記のように書き、関数ブロックの中に
// #ifdefは書かない。

#ifdef DEBUG
#define DEBUG_COUT() std::cout << __func__ << ":" << __LINE__ << std::endl
#else
#define DEBUG_COUT()
#endif

bool g() noexcept
{
    DEBUG_COUT();

    // @@@ ignore begin
    // @@@ ignore end

    return false;
}

// @@@ sample end

// @@@ sample begin 0:1

#define GEN_SYMBOL(x_, y_) x_##y_

int32_t h() noexcept
{
    int32_t GEN_SYMBOL(a, b);  // int ab;と同じ

    ab = 3;

    return ab;
}
// @@@ sample end
}  // namespace PreprocessorSample

namespace ShippingSample {

namespace NG {
#define SHIP_TO_JAPAN
// @@@ sample begin 0:2
//
// ヘッダファイルでの宣言(NGのパターン)
//

enum class ShippingRegions { Japan, US, EU };

struct ShippingData {
    // 何らかの宣言
};

void ShippingDoSomething(ShippingData const& region_data);

#if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG

constexpr ShippingRegions shipping_region = ShippingRegions::Japan;

ShippingData const region_data{
    // 何らかのデータ
};

#elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG

constexpr ShippingRegions shipping_region = ShippingRegions::US;
ShippingData const region_data{
    // 何らかのデータ
};

#elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // NG

constexpr ShippingRegions shipping_region = ShippingRegions::EU;
ShippingData const        region_data{
    // 何らかのデータ
};

#else
static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
#endif

//
// .cppファイルでの定義(NGのパターン)
//
void ShippingDoSomething(ShippingData const& region_data)
{
    IGNORE_UNUSED_VAR(region_data);                                         // @@@ delete
#if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG
    // 何らかの処理
#elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG
    // 何らかの処理
#elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // NG
    // 何らかの処理
#else
    static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
#endif
}
// @@@ sample end

namespace {
TEST(ProgrammingConvention, compile_switch)
{
    static_assert(shipping_region == ShippingRegions::Japan);
    IGNORE_UNUSED_VAR(region_data);
}
}  // namespace
}  // namespace NG

namespace OK {
#define SHIP_TO_JAPAN
// @@@ sample begin 0:3
//
// ヘッダファイルでの宣言(OKのパターン)
//

enum class ShippingRegions { Japan, US, EU };

struct ShippingData {
    // 何らかの宣言
    ShippingRegions shipping_region;  // @@@ delete
};
void ShippingDoSomething(ShippingData const& region_data);

extern ShippingData const& region_data;

#if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK

constexpr ShippingRegions shipping_region = ShippingRegions::Japan;

#elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK

constexpr ShippingRegions shipping_region = ShippingRegions::US;

#elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // OK

constexpr ShippingRegions shipping_region = ShippingRegions::EU;

#else
static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
#endif

//
// .cppファイルでの定義(OKのパターン、以下にはプリプロセッサ命令は出てこない)
//

void ShippingDoSomething(ShippingData const& region_data)
{
    IGNORE_UNUSED_VAR(region_data);  // @@@ delete
    if constexpr (shipping_region == ShippingRegions::Japan) {
        // 何らかの処理
    }
    else if constexpr (shipping_region == ShippingRegions::US) {
        // 何らかの処理
    }
    else if constexpr (shipping_region == ShippingRegions::EU) {
        // 何らかの処理
    }
    else {
        static_assert(shipping_region == ShippingRegions::Japan || shipping_region == ShippingRegions::US
                      || shipping_region == ShippingRegions::EU);
    }
}

template <ShippingRegions sr>
ShippingData const& gen_shipping_data()
{
    if constexpr (sr == ShippingRegions::Japan) {
        static ShippingData const region_data{
            // 何らかのデータ
            ShippingRegions::Japan  // @@@ delete
        };
        return region_data;
    }
    else if constexpr (sr == ShippingRegions::US) {
        static ShippingData const region_data{
            // 何らかのデータ
            ShippingRegions::US  // @@@ delete
        };
        return region_data;
    }
    else if constexpr (sr == ShippingRegions::EU) {
        static ShippingData const region_data{
            // 何らかのデータ
            ShippingRegions::EU  // @@@ delete
        };
        return region_data;
    }
    else {
        static_assert(sr == ShippingRegions::Japan || sr == ShippingRegions::US || sr == ShippingRegions::EU);
    }
}

ShippingData const& region_data = gen_shipping_data<shipping_region>();
// @@@ sample end

namespace {
TEST(ProgrammingConvention, compile_switch)
{
    static_assert(shipping_region == ShippingRegions::Japan);
    ASSERT_EQ(ShippingRegions::Japan, region_data.shipping_region);
}
}  // namespace
}  // namespace OK
}  // namespace ShippingSample
namespace MacroFunctionSample {

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_SIZEOF_POINTER_DIV;
SUPPRESS_WARN_SIZEOF_ARRAY_ARG;

// @@@ sample begin 1:0

#define ARRAY_LENGTH(array_) (sizeof(array_) / sizeof(array_[0]))  // NG

template <typename T, size_t N>  // OK
constexpr size_t array_length(T const (&)[N]) noexcept
{
    return N;
}

// arrayは配列へのリファレンスだが関数中では配列
size_t f0(bool use_macro, int32_t (&array)[5]) noexcept
{
    if (use_macro) {
        return ARRAY_LENGTH(array);  // この場合は、関数型マクロでも正しく処理できるが好ましくない
    }
    else {
        return array_length(array);  // OK
    }
}

// fake_arrayは配列に見えるが実際にはポインタ
size_t f1(bool use_macro, int32_t fake_array[5]) noexcept
{
    if (use_macro) {
        return ARRAY_LENGTH(fake_array);  // NG 誤用でもコンパイルできてしまい不正値を返す
    }
    else {
        // return  array_length(fake_array); // OK 誤用のためコンパイルエラー
        auto array = reinterpret_cast<int32_t(*)[5]>(fake_array);  // 無理やりコンパイル
        return array_length(*array);
    }
}
// @@@ sample end
//

SUPPRESS_WARN_CLANG_UNUSED_CONST_VAR;
namespace {
TEST(ProgrammingConvention, macro_func)
{
    int32_t array[5];

    ASSERT_EQ(5, f0(true, array));
    ASSERT_EQ(5, f0(false, array));
    ASSERT_EQ(2, f1(true, array));  // ARRAY_LENGTHの誤用
    ASSERT_EQ(5, f1(false, array));
}
}  // namespace

}  // namespace MacroFunctionSample
namespace MacroConstantVarSample {
// @@@ sample begin 2:0

#define XXX_LENGHT 5  // NG

constexpr uint32_t YyyLenght{5};  // OK

#define XXX_TYPE_A 0  // NG
#define XXX_TYPE_B 1  // NG
#define XXX_TYPE_C 2  // NG

enum class XxxType {  // OK
    A = 0,            //      Aの値が必要だと前提
    B,
    C
};
// @@@ sample end

SUPPRESS_WARN_END;

}  // namespace MacroConstantVarSample
