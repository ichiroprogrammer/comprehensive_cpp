#include <sys/wait.h>
#include <unistd.h>

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_SIGN_COMPARE;
SUPPRESS_WARN_DEL_INCOMP;
SUPPRESS_WARN_GCC_NOT_EFF_CPP;
SUPPRESS_WARN_GCC_UNINIT;

TEST(CodeAnalysis, signed_to_unsigned)
{
    // @@@ sample begin 0:0

    int32_t  x{-1};
    uint32_t y{1};

    bool b0{x < y};
    ASSERT_FALSE(b0);  // 数学では成立する x < y が成立しない

    ++x, ++y;
    bool b1{x < y};
    ASSERT_TRUE(b1);  // x、yが正になれば x < y が成立する
    // @@@ sample end
}

class X {
public:
    int32_t const& GetA() const noexcept { return a_; }

private:
    int32_t a_{0};
};

// @@@ sample begin 0:1

class Pimpl {
public:
    Pimpl();
    ~Pimpl() { delete core_; }  // 不完全型のdelete
private:
    class PimplCore;
    PimplCore* core_;
};

class Pimpl::PimplCore {
public:
    PimplCore() : x_{new X} {}
    ~PimplCore() { delete x_; }  // ~PimplCore()から呼び出されない

private:
    X* x_;
};

Pimpl::Pimpl() : core_{new PimplCore} {}

void incomplete_class()
{
    // ~Pimpl()では、クラスPimplCoreが不完全型なので~PimplCore()が呼び出されないため、
    // x_の解放がされずメモリリークする
    auto pimpl = Pimpl{};
}
// @@@ sample end
SUPPRESS_WARN_PESSIMIZING_MOVE;
// @@@ sample begin 0:2

std::string prevent_copy_elision()
{
    auto ret = std::string{"prevent copy elision"};

    return std::move(ret);  // std::moveのためにRVOが阻害される
}

void rvo_inhibition()
{
    // RVOが機能すればstd::stringのコンストラクタは一度だけ呼び出される
    std::string a = prevent_copy_elision();
}
// @@@ sample end
SUPPRESS_WARN_CLANG_OVERLOADED_VIRTUAL;
// @@@ sample begin 1:0

class OverloadVirtualBase {
public:
    OverloadVirtualBase()          = default;
    virtual ~OverloadVirtualBase() = default;
    virtual void DoSomething(int32_t) noexcept  // 派生クラスがオーバーライドできる。
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
};

class OverloadVirtualDerived : public OverloadVirtualBase {
public:
    // シグネチャが異なるためOverloadVirtualBase::DoSomethingのオーバーライドではない。
    virtual void DoSomething(uint32_t) noexcept
    {
        // @@@ ignore begin
        // @@@ ignore end
    }
};
// @@@ sample end
// @@@ sample begin 2:0

class IllegalShallowCopy {
public:
    IllegalShallowCopy() : x_{new X} {}
    ~IllegalShallowCopy() { delete x_; }

private:
    X* x_;
};

void illegal_shallow_copy()
{
    auto a = IllegalShallowCopy{};
    auto b = IllegalShallowCopy{};

    a = b;  // a.x_ = b.x_が行われるため、代入前のa.x_は解放されず、
            // 代入後のb.x_は2度deleteされる
}
// @@@ sample end

int32_t global{1};

// @@@ sample begin 2:1

void potential_leak()
{
    X* x{new X};

    if (global == 2) {  // globalが2ならメモリリーク
        return;
    }

    delete x;
}
// @@@ sample end

// @@@ sample begin 3:0

int32_t array_access(int32_t index)
{
    uint32_t array[8]{};

    return array[index];
}

void array_stask_read_overflow()
{
    array_access(8);  // off-by-1 このようなコードは意外なほど多い
}
// @@@ sample end

// @@@ sample begin 4:0

class NonVirtualDestructorBase {
public:
    NonVirtualDestructorBase() noexcept {}
    ~NonVirtualDestructorBase() { std::cout << __func__ << std::endl; }
};

class NonVirtualDestructorDerived : public NonVirtualDestructorBase {
public:
    NonVirtualDestructorDerived(char const* str) : str_{std::make_unique<std::string>(str)} {}
    ~NonVirtualDestructorDerived() { std::cout << __func__ << std::endl; }
    std::string const& Get() const noexcept { return *str_; }

private:
    std::unique_ptr<std::string> str_;
};

void non_virtual_destructor()
{
    // ~NonVirtualDestructorBase()が非virtualであるため、aの解放時に~NonVirtualDestructorDerived()
    // が呼び出されないことによってNonVirtualDestructorDerived::str_はリークする。
    std::unique_ptr<NonVirtualDestructorBase> a{std::make_unique<NonVirtualDestructorDerived>("D")};
}
// @@@ sample end
SUPPRESS_WARN_UNUSED_VAR;

void access_deleted_memory()
{
    int32_t const* a;

    {
        auto x_ptr = std::make_unique<X>();
        a          = &x_ptr->GetA();
    }
    auto b = *a;
    IGNORE_UNUSED_VAR(b);  // @@@ delete
}

void access_after_scope() noexcept
{
    int32_t const& a = X{}.GetA();

    auto b = a;
    IGNORE_UNUSED_VAR(b);  // @@@ delete
}

void array_fill(uint32_t array[8]) noexcept  // arrayは配列でなくポインタ
{
    for (auto i = 0; i < 8; ++i) {
        array[i] = 0;
    }
}

void array_stask_write_overflow() noexcept
{
    uint32_t array[7]{};

    array_fill(array);
}

uint32_t array[7]{};

void array_global_write_overflow() noexcept
{
    array_fill(array);  // array_fillの仮引数型は、uint32_t*
}

void pointer_overflow() noexcept
{
    uint32_t  array[8]{};
    uint32_t* x;

    x      = array + 8;
    auto y = *x;           // off-by-1のポインタデリファレンス
    IGNORE_UNUSED_VAR(y);  // @@@ delete
}

int32_t shift(int32_t x, int32_t y) noexcept { return x << y; }

void shift_minus() noexcept
{
    shift(10, -1);  // 左シフトの右オペランドは正でなければならない
}

SUPPRESS_WARN_CLANG_UNDEF_COMP;
SUPPRESS_WARN_GCC_NON_NULL_COMP;
class NullObj {  // Null Object Patternではない
public:
    char const* Get() noexcept
    {
        if (this == nullptr) {
            return "null";
        }
        return a_;
    }

private:
    char const* a_ = "not null";
};

void null_object() noexcept
{
    NullObj* n(nullptr);

    n->Get();
}

SUPPRESS_WARN_RETURN_TYPE;
int32_t non_return_statement() noexcept
{
    // return無しでもコンパイルはできる
}

void non_return() noexcept { non_return_statement(); }

TEST(CodeAnalysis, signed_int_overflow)
{
    auto si08 = std::numeric_limits<int8_t>::max();

    ASSERT_EQ(127, si08);
    ++si08;  // sanitizerはこのオーバーフローを検出しない
    ASSERT_EQ(-128, si08);

    auto si16 = std::numeric_limits<int16_t>::max();

    ASSERT_EQ(32767, si16);
    si16++;  // sanitizerはこのオーバーフローを検出しない
    ASSERT_EQ(-32768, si16);

    auto si32 = std::numeric_limits<int32_t>::max();

    ASSERT_EQ(2147483647, si32);
    si32++;  // sanitizerはこのオーバーフローを検出する
    ASSERT_EQ(-2147483648, si32);

    auto si64 = std::numeric_limits<int64_t>::max();

    ASSERT_EQ(9223372036854775807, si64);
    si64++;                           // sanitizerはこのオーバーフローを検出する
    auto exp = -9223372036854775807;  // 最大長を超えるため、-9223372036854775808は記述できない
    ASSERT_EQ(--exp, si64);
}

float div(float x, int32_t y) noexcept { return x / y; }

void float_div_by_zero() noexcept { div(3.0F, 0); }

void int_div_by_minus() noexcept
{
    auto a = std::numeric_limits<int32_t>::min();

    a /= -1;
    IGNORE_UNUSED_VAR(a);
}

struct Y {
    uint8_t buff[12];
};

void illegal_alignment() noexcept
{
    Y    y;
    auto a = reinterpret_cast<uint64_t*>(y.buff + 4);

    auto b = *a;
    IGNORE_UNUSED_VAR(b);
}
SUPPRESS_WARN_END;

void (*const code_analysis_funcs[])(){
    non_virtual_destructor,
    illegal_shallow_copy,
    incomplete_class,
    rvo_inhibition,
    potential_leak,
    access_deleted_memory,
    access_after_scope,
    array_stask_read_overflow,
    array_stask_write_overflow,
    array_global_write_overflow,
    float_div_by_zero,
    pointer_overflow,
    shift_minus,
    null_object,
    non_return,
    int_div_by_minus,
    illegal_alignment,
};

void exec_background(void (*f)())
{
    auto const pid = fork();

    if (pid < 0) {
        return;
    }

    if (pid == 0) {
        f();
        exit(0);
    }
    else {
        auto status = 0;
        wait(&status);
    }
}

void all()
{
    for (auto const& f : code_analysis_funcs) {
        exec_background(f);
    }
}

TEST(CodeAnalysis, others) { all(); }

TEST(CodeAnalysis, float_cast_overflow)
{
    // @@@ sample begin 4:1

    float x{0x1'0000'0000};
    // int32_t y{x};  // yのレンジを超えるため、コンパイルエラー
    int32_t y = x;
    // @@@ sample end
    IGNORE_UNUSED_VAR(y);
}
