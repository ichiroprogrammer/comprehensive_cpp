#pragma once

#include <cstdint>

namespace ScopeSample {

// @@@ sample begin 0:0

extern uint32_t xxx;  // NG 外部から参照可能な静的変数
extern uint64_t yyy;  // NG 同上
// @@@ sample end
}  // namespace ScopeSample
