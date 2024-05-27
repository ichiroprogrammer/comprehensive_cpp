#include "gtest_wrapper.h"

#ifdef __CYGWIN__  // cygwinでは、ASSERT_DEATHを使わない
#define ProgrammingConventionFuncA_Opt DISABLED_ProgrammingConventionFuncA
#else  // __linux__
#define ProgrammingConventionFuncA_Opt ProgrammingConventionFuncA
#endif

namespace {
// @@@ sample begin 0:0
// [A]
// 下記FloatingPointは、Tが浮動小数点型、Tのインスタンスは非０であることを前提としている。
// 適切にアサーションを挿入して誤用を防げ。

template <typename T>
class FloatingPoint {
public:
    static_assert(std::is_floating_point_v<T>, "T must be floating point type");
    FloatingPoint(T num) noexcept : num_{num} { assert(num != 0); }

    T Get() const noexcept { return num_; }
    T Reciprocal() const noexcept { return 1 / num_; }

private:
    T const num_;
};

TEST(ProgrammingConventionFuncA_Opt, Assertion)
{
    auto f1 = FloatingPoint<float>{1.0F};
    auto d1 = FloatingPoint<double>{1.0};

    ASSERT_EQ(f1.Get(), 1.0F);
    ASSERT_EQ(d1.Get(), 1.0);
    ASSERT_DEATH(FloatingPoint<float>{0}, "num != 0");
    ASSERT_DEATH(FloatingPoint<double>{0}, "num != 0");

#if 0  // コンパイルできない。
    auto i = FloatingPoint<int32_t>{1};
#endif
}
// @@@ sample end

}  // namespace
