#pragma once
#include <chrono>

// @@@ sample begin 0:0

// パフォーマンス測定用
template <typename FUNC>
std::chrono::milliseconds MeasurePerformance(uint32_t count, FUNC f)
{
    auto const start = std::chrono::system_clock::now();

    for (auto i = 0U; i < count; ++i) {
        f();
    }

    auto const stop = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}
// @@@ sample end
