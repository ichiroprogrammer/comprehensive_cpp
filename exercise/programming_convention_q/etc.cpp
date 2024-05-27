#include "gtest_wrapper.h"

namespace {
// @@@ sample begin 0:0
// [Q]
// 下記FloatingPointは、Tが浮動小数点型、Tのインスタンスは非０であることを前提としている。
// 適切にアサーションを挿入して誤用を防げ。

template <typename T>
class FloatingPoint {
public:
    FloatingPoint(T num) noexcept : num_{num} {}
    T Get() const noexcept { return num_; }
    T Reciprocal() const noexcept { return 1 / num_; }

private:
    T num_;
};
// @@@ sample end
}  // namespace
