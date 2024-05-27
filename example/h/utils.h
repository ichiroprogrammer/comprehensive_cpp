#pragma once
#include <cstdint>

constexpr uint32_t Roundup(uint32_t multiple, uint32_t num_to_round) noexcept
{
    return ((num_to_round + multiple - 1) / multiple) * multiple;
}

template <typename T, size_t N>
constexpr size_t ArrayLength(T const (&)[N]) noexcept
{
    return N;
}

template <typename HEAD, typename... TAILS>
constexpr size_t MaxSizeof()
{
    if constexpr (sizeof...(TAILS) == 0) {
        return sizeof(HEAD);
    }
    else {
        return std::max(sizeof(HEAD), MaxSizeof<TAILS...>());
    }
}
