#include <cassert>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace ConsConstexprSample {
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_CLANG_UNUSED_CONST_VAR;

char const* get_str() { return "hoge"; }

// @@@ sample begin 0:0

// name0は文字列リテラルを指すポインタなのでconstでなければならない。
char const* name0 = "hoge";

// name1は文字列リテラルでないのでconstでなくてよい。
char name1[] = "hoge";

char const* get_str();
// 左側のconstはname2の指す先をconstにする。
// 右側のconstはname2自体をconstにする。
char const* const name2 = get_str();

// name2の右辺がリテラルならば、下記のようにするべきである。
constexpr char const* name3 = "hoge";

void f(std::vector<int32_t>& vec)
{
    std::vector<int32_t>::iterator const iter = vec.begin();  // iter自体がconst

    *iter = 10;
    // ++iter;      // 意図的にコンパイルエラー

    std::vector<int32_t>::const_iterator const_iter_0 = vec.begin();   // *const_iter_0がconst
    auto                                 const_iter_1 = vec.cbegin();  // *const_iter_1がconst
    static_assert(std::is_same_v<std::vector<int32_t>::const_iterator, decltype(const_iter_1)>);

    // *const_iter_0 = 10;   // 意図的にコンパイルエラー
    ++const_iter_0;

    // *const_iter_1 = 10;   // 意図的にコンパイルエラー
    ++const_iter_1;

    // @@@ ignore begin
    // @@@ ignore end
}
// @@@ sample end

// constの位置の例のため、このファイルをwesterlyでformatしてはならない
// @@@ sample begin 0:1

const std::string s;  // NG
std::string const t;  // OK

const std::string* s_ptr;  // NG
std::string const* t_ptr;  // OK

const std::string& f();  // NG 関数の宣言
std::string const& g();  // OK 関数の宣言

char        abc[]{"abc"};
const char* a = abc;  // NG *aはconst
char const* b = abc;  // OK *aはconst
char* const c = abc;  // NG *aではなく、aがconstになり、意味が変わる

const char* const d = abc;  // NG
char const* const e = abc;  // OK
// @@@ sample end
SUPPRESS_WARN_END;
}  // namespace ConsConstexprSample
