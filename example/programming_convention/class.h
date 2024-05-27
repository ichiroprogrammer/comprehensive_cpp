#pragma once
#include <cstdint>

namespace StaticMemberVarInitializationSample {
// @@@ sample begin 0:0

class StaticConstexprVar {
public:
    StaticConstexprVar() = default;

    uint32_t MultiplyBy2(uint32_t a) noexcept;
    uint32_t MultiplyBy3(uint32_t a) noexcept { return static_constexpr_var_3 * a; }
    uint32_t MultiplyBy4(uint32_t a) noexcept;

private:
    static constexpr uint32_t static_constexpr_var_2{2};  // NG クラス内で定義する必要なし
    static constexpr uint32_t static_constexpr_var_3{3};  // OK クラス内で定義する必要あり
};
// @@@ sample end
}  // namespace StaticMemberVarInitializationSample
