#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>

#include "suppress_warning.h"

// このファイルはclang-format offにする。
// clang-format off

namespace IndentChar {
// @@@ sample begin 0:0

int32_t f0() noexcept
{
  auto var_x = 0;          // NG インデントが2スペース
  return var_x;
}

int32_t f1() noexcept
{
        auto var_x = 0;    // NG インデントが8スペース
        return var_x;
}

int32_t f2() noexcept
{
	int32_t var_x{0};        // NG  インデントがハードタブ
	return var_x;
}

int32_t f3() noexcept
{
    auto var_x = 0;        // OK
    return var_x;
}
// @@@ sample end
}  // namespace IndentChar

namespace SwitchCaseDefaultIndent {

int32_t f(int32_t var_a) noexcept
{
    auto var_b = 0;

    // @@@ sample begin 1:0

    switch (var_a) {
    case 1: {                   // OK
        var_b = 1;
        break;
    }
        case 2:                 // NG caseのインデントはswitchと同じカラム
            {                   // NG {は"case 2: "の直後
                var_b = 2;
                break;
            }                   // NG caseと同じカラム
    case 3:
    var_b = 3;                  // NG caseから1インデント下げる
    break;
    case 4: var_b = 4;          // NG caseの行にそのまま処理を続けない
        break;
    default:                    // OK
        break;
    }
    // @@@ sample end

    return var_b;
}

}  // namespace SwitchCaseDefaultIndent

namespace BlockStyle {

// @@@ sample begin 2:0

void f0(int32_t var_x, int32_t* var_y) noexcept { // NG {の前に改行
    if (var_x == 0)
    {                                   // NG
        *var_y = 0;
    }
    else
    {                                   // NG
        *var_y = 10;
    }
    return;
}

void f1(int32_t var_x, int32_t* var_y) noexcept
{                                       // OK
    if (var_x == 0) {                   // OK
        *var_y = 0;
    }
    else {                              // OK
        *var_y = 1;
    }
    return;
}

void f2(int32_t var_x, int32_t* var_y) noexcept
{                                       // OK
    if (var_x > 0)                      // NG )の後の改行不要
    {
        *var_y = 0;
    }

    if (var_x == 0)                     // NG )の後の改行不要
    {
        *var_y = 0;
    }
    else {                              // OK
        var_x = 3;
    }

    if (var_x == 0)                     // NG
    {
        *var_y = 0;
    } else                              // NG else前に改行。後ろは1スペース開けて{
    {                                   //    
        var_x = 3;
    }

    if (var_x == 0)                     // NG if文と同じ行に{
    {
        *var_y = 0;
    }
    else                                // NG 
    {
        *var_y = 3;
    }

    return;
}
// @@@ sample end
}  // namespace BlockStyle

namespace ArgumentStyle {

// @@@ sample begin 3:0

void function();            // OK
void function(int32_t foo,  // OK
              int32_t bar);
void funcction(             // OK 
        int32_t foo,
        int32_t bar
        );
void function(int32_t hoge
              );            // NG
void function               // NG (は関数の直後
        (
         int32_t hoge,
         char  foo
         );
// @@@ sample end
}  // namespace ArgumentStyle

namespace ClassStyle {

// @@@ sample begin 4:0

class A {
    public:         // NG
        void B();
private:            // OK
    void C();
};
// @@@ sample end
}  // namespace ClassStyle

namespace SpaceStyle {
void g() noexcept {}

void f(int32_t) noexcept
{
    // @@@ sample begin 5:0

    for (;;) {                          // OK forの後ろにはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }

    for(;;){                            // NG forの後ろにはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }

    try {                               // OK tryの後ろにはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch (std::exception const& e) {   // OK catchの後ろと{の前にはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }

    try{                                // NG tryの後ろにはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }
    catch(std::exception const& e){     // NG catchの後ろと{の前にはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }

    g();                                // OK 関数の後ろにはスペース無し

    g ();                               // NG
    // @@@ sample end
}

}  // namespace SpaceStyle

namespace AfterCommaStyle {
void g(char const*, int32_t) noexcept {}

void f(int32_t a) noexcept
{
    // @@@ sample begin 6:0

    for (int32_t i{0}, j{0}; i + j < 10; ++i, ++j) {  // OK
        // @@@ ignore begin
        // @@@ ignore end
    }

    for (int32_t i{0},j{0}; i + j < 10; ++i,++j) {    // NG ,の後ろにはスペース
        // @@@ ignore begin
        // @@@ ignore end
    }

    g("%d print tooooooooooooooooooooooooooooooooo many characters.",
      a);                                // OK ,の直後、スペース無し ↑
    // @@@ sample end
}
}  // namespace AfterCommaStyle

namespace OperatorStyle {
char const* f(int32_t& var_a, int32_t (&var_b)[3], int32_t& var_c, std::string& var_d) noexcept
{
    // @@@ sample begin 7:0

    var_a=0;                        // NG
    var_a = 0;                      // OK

    var_b[ 1 ] = 1;                 // NG
    var_b[2] = 1;                   // OK

    var_c+=3;                       // NG
    var_c += 3;                     // OK

    if(var_a == *var_b) {           // OK
        return var_d .c_str();      // NG
    }
    else {
        return var_d.c_str() + 1;   // OK
    }
    // @@@ sample end
}
}  // namespace OperatorStyle

namespace ConditionalOperatorStyle {
bool f(bool condition, int32_t a, int32_t b, bool x, bool y) noexcept
{
    // @@@ sample begin 8:0

    auto ret = condition ? x : y;  // ワンライナーが基本

    auto ret2 = (a > b) ? x        // 行が長すぎる場合
                        : y;
    // @@@ sample end

    return ret && ret2;
}

int32_t f(int32_t a, int32_t b, int32_t c, int32_t d, int32_t x) noexcept
{
    // @@@ sample begin 8:1

    auto max = (a > b) ? a :
               (b > c) ? b : 
               (c > d) ? c : 
               // @@@ ignore begin
               // @@@ ignore end
                         x;
    // @@@ sample end

    return max;
}
}  // namespace ConditionalOperatorStyle

namespace PointerReferneceStyle {

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_UNUSED_VAR;

void f(int32_t i) noexcept
{
    // @@@ sample begin 9:0

    char* a;  // OK
    char *b;  // NG 型の直後に*

    int32_t& j{i};  // OK
    // @@@ sample end
    // @@@ sample begin 9:1

    char*   c, d;  // NG dはchar*ではない
    int32_t e, f;  // NG
    // @@@ sample end
}
}  // namespace PointerReferneceStyle
SUPPRESS_WARN_END;

namespace ColumnStyle {

// @@@ sample begin 10:0

int32_t f(int32_t arg1,  // OK
          int32_t arg2,
          int32_t arg3) noexcept;

int32_t g(  // OK
    int32_t arg1,
    int32_t arg2,
    int32_t arg3) noexcept;
// @@@ sample end
// @@@ sample begin 10:1

int32_t f(int32_t arg1,  // OK
          int32_t arg2,
          int32_t arg3) noexcept
{
    return arg1 + arg2 + arg3;
}

int32_t g(  // OK
    int32_t arg1,
    int32_t arg2,
    int32_t arg3) noexcept
{
    return arg1 + arg2 + arg3;
}
// @@@ sample end

int32_t h(int32_t arg1, int32_t arg2, int32_t arg3) noexcept
{
    // @@@ sample begin 10:2

    int32_t ret{f(arg1,
                  arg2,
                  arg3)};
    // @@@ sample end
    // @@@ sample begin 10:3

    if (((arg1 == arg2) && (arg2 == arg3))
      || (arg3 == 3)) {
        ret = 0;
    }
    // @@@ sample end

    // @@@ sample begin 10:4

    auto some_looooooooooooooooooooog_variable  // 式の最後までが100カラムに入らない場合
         = arg1 + 1;
    // @@@ sample end

    // @@@ sample begin 10:5

    std::cout << "foobarfubarhoge"
                 "hugahogehoge"
                 "1234567890";  // 長い文字列は分割
    // @@@ sample end

    return ret + some_looooooooooooooooooooog_variable;
}
}  // namespace ColumnStyle

namespace BlockLogicalLevelStyle {
struct Buffer_t {
    int32_t  len;
    uint8_t* buff;
};

Buffer_t* PrepareBuffer() noexcept { return nullptr; }
void      ReadFromStream(Buffer_t&) noexcept {}
void      WriteToStorage(Buffer_t const&) noexcept {}
void      DestroyBuffer(Buffer_t* buff) noexcept
{
    delete[] buff->buff;
    delete buff;
}

// @@@ sample begin 11:0

void DoSomethingNG() noexcept  // NG
{
    Buffer_t* buff{new Buffer_t};           // NG 抽象度が低すぎる
                                            //
    buff->len  = 1024;                      //
    buff->buff = new uint8_t[buff->len];    //
    std::memset(buff->buff, 0, buff->len);  //

    ReadFromStream(*buff);
    WriteToStorage(*buff);

    DestroyBuffer(buff);
}

void DoSomethingOK() noexcept  // OK
{
    Buffer_t* buff = PrepareBuffer();

    ReadFromStream(*buff);
    WriteToStorage(*buff);

    DestroyBuffer(buff);
}
// @@@ sample end

}  // namespace BlockLogicalLevelStyle

// @@@ sample begin 12:0
namespace event {

class A {  // インデントなし
    // @@@ ignore begin
    // @@@ ignore end
};

// @@@ ignore begin
// @@@ ignore end

namespace {

void f() noexcept;  // インデントなし
// @@@ ignore begin
void f() noexcept {}
// @@@ ignore end

}  // namespace

// @@@ ignore begin
void g() noexcept { f(); }
// @@@ ignore end
}  // namespace event
// @@@ sample end
// clang-format on
