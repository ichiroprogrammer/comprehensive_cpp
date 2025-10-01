#pragma once
#include <algorithm>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <vector>

namespace Nstd {
template <typename T, size_t N>
constexpr size_t ArrayLength(T const (&)[N]) noexcept
{
    return N;
}

template <typename T>
void SortUnique(std::vector<T>& v)
{
    std::sort(v.begin(), v.end());
    auto result = std::unique(v.begin(), v.end());
    v.erase(result, v.end());
}

template <typename T>
void SortUnique(std::list<T>& v)
{
    v.sort();
    v.unique();
}

template <typename T>
void Concatenate(std::vector<T>& v0, std::vector<T>&& v1)
{
    for (auto& v1_elem : v1) {
        v0.insert(v0.end(), std::move(v1_elem));
    }
}

template <typename T>
void Concatenate(std::list<T>& v0, std::list<T>&& v1)
{
    v0.splice(v0.end(), std::move(v1));
}

template <typename F>
class ScopedGuard {
public:
    explicit ScopedGuard(F&& f) noexcept : f_{f} {}
    ~ScopedGuard() { f_(); }
    ScopedGuard(ScopedGuard const&)            = delete;
    ScopedGuard& operator=(ScopedGuard const&) = delete;

private:
    F f_;
};

inline std::string Replace(std::string in, std::string_view from, std::string_view to)
{
    auto pos = in.find(from);

    while (pos != std::string::npos) {
        in.replace(pos, from.length(), to);
        pos = in.find(from, pos + to.length());
    }

    return in;
}

//
// operator<< for range
//
namespace Inner_ {
//
// exists_put_to_as_member
//
template <typename, typename = std::ostream&>
struct exists_put_to_as_member : std::false_type {
};

template <typename T>
struct exists_put_to_as_member<T, decltype(std::declval<std::ostream&>().operator<<(
                                      std::declval<T>()))> : std::true_type {
};

template <typename T>
constexpr bool exists_put_to_as_member_v{exists_put_to_as_member<T>::value};

//
// exists_put_to_as_non_member
//
template <typename, typename = std::ostream&>
struct exists_put_to_as_non_member : std::false_type {
};

template <typename T>
struct exists_put_to_as_non_member<T, decltype(operator<<(std::declval<std::ostream&>(),
                                                          std::declval<T>()))> : std::true_type {
};

template <typename T>
constexpr bool exists_put_to_as_non_member_v{exists_put_to_as_non_member<T>::value};

//
// exists_put_to_v
//
template <typename T>
constexpr bool exists_put_to_v{
    Nstd::Inner_::exists_put_to_as_member_v<T> || Nstd::Inner_::exists_put_to_as_non_member_v<T>};

//
// is_range
//
template <typename, typename = bool>
struct is_range : std::false_type {
};

template <typename T>
struct is_range<T, typename std::enable_if_t<!std::is_array_v<T>,
                                             decltype(std::begin(std::declval<T>()), bool{})>>
    : std::true_type {
};

template <typename T>
struct is_range<T, typename std::enable_if_t<std::is_array_v<T>, bool>> : std::true_type {
};

//
// is_range_v
//
template <typename T>
constexpr bool is_range_v{is_range<T>::value};

}  // namespace Inner_

//
// operator<< for range
//
template <typename T>
auto operator<<(std::ostream& os, T const& t) ->
    typename std::enable_if_t<Inner_::is_range_v<T> && !Inner_::exists_put_to_v<T>, std::ostream&>
{
    auto first = true;

    for (auto const& i : t) {
        if (!std::exchange(first, false)) {
            os << ", ";
        }
        os << i;
    }

    return os;
}
}  // namespace Nstd
