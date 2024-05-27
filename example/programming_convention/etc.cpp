#include <cstdint>

// このファイルは、suppress_warning.hをインクルードしない

namespace AssertionSample {

template <typename... ARGS>
inline void IGNORE_UNUSED_VAR(ARGS&...) noexcept
{
}

// @@@ sample begin 0:0

template <uint32_t SIZE>
struct POD {
    POD() noexcept
    {  // 何らかの理由で、10を超えるSIZEをサポートしたくない。
        static_assert(SIZE < 10, "too big");
    }

    uint32_t mem[SIZE];
};

void f() noexcept
{
    POD<3> p3;             // コンパイル可能
    auto   p4 = POD<4>{};  // コンパイル可能
    // POD<10> p10;        // static assertion failed: too big でコンパイルエラー
    // POD<11> p11;        // static assertion failed: too big でコンパイルエラー
    IGNORE_UNUSED_VAR(p3, p4);  // @@@ delete
}
// @@@ sample end

}  // namespace AssertionSample

namespace PragmaSample {

// @@@ sample begin 1:0

#if defined(__clang__)
#define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD \
    _Pragma("clang diagnostic ignored \"-Wunused-private-field\"")
#else
#define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD
#endif

#define SUPPRESS_WARN_GCC_BEGIN _Pragma("GCC diagnostic push")
#define SUPPRESS_WARN_GCC_END _Pragma("GCC diagnostic pop")
#define SUPPRESS_WARN_GCC_NOT_EFF_CPP _Pragma("GCC diagnostic ignored \"-Weffc++\"")
#define SUPPRESS_WARN_GCC_UNUSED_VAR _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")

//
// ...
//

SUPPRESS_WARN_GCC_BEGIN;
SUPPRESS_WARN_GCC_UNUSED_VAR;
SUPPRESS_WARN_GCC_NOT_EFF_CPP;
SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;

class A {
public:
    A() noexcept
    {
        // 警告: 'PragmaSample::A::b_' should be initialized in
        //       the member initialization list [-Weffc++]
        // 警告: unused variable 'c' [-Wunused-variable]
        // のようなワーニングが出力される。

        int32_t c;
        b_ = 0;
    }

private:
    int32_t a_{0};
    int32_t b_;
};

SUPPRESS_WARN_GCC_END;
// @@@ sample end
}  // namespace PragmaSample
