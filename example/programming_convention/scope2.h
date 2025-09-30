#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace ScopeSample {

// @@@ sample begin 0:0

template <size_t N>
class StaticString {  // StaticStringは外部公開
    // @@@ ignore begin
public:
    constexpr StaticString(char const (&str)[N]) noexcept : StaticString{str, std::make_index_sequence<N - 1>{}} {}

    constexpr StaticString(std::initializer_list<char> args) noexcept
        : StaticString{args, std::make_index_sequence<N - 1>{}}
    {
    }

    constexpr char const (&String() const noexcept)[N] { return string_; }
    constexpr size_t Size() const noexcept { return N; }

private:
    char const string_[N];

    template <typename T, size_t... I>
    constexpr StaticString(T& t, std::index_sequence<I...>) noexcept : string_{std::begin(t)[I]...}
    {
        static_assert(std::is_same_v<T, std::initializer_list<char>> || std::is_same_v<T, char const[N]>);
        static_assert(N - 1 == sizeof...(I));
    }
    // @@@ ignore end
};

namespace Inner_ {  // equal_nは外部非公開
template <size_t N>
constexpr bool equal_n(size_t n, StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
{
    if (n == N) {
        return true;
    }
    else {
        return lhs.String()[n] != rhs.String()[n] ? false : equal_n(n + 1, lhs, rhs);
    }
}
}  // namespace Inner_

template <size_t N1, size_t N2>  // operator==は外部公開
constexpr bool operator==(StaticString<N1> const&, StaticString<N2> const&) noexcept
{
    return false;
}

template <size_t N>  // operator==は外部公開
constexpr bool operator==(StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
{
    return Inner_::equal_n(0, lhs, rhs);
}
// @@@ sample end
}  // namespace ScopeSample
