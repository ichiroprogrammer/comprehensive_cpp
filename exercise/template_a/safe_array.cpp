#include <array>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// std::array、std::vector、std::string等のSTLの配列型コンテナはインデックスアクセスに対して、
// レンジのチェックをしないため、不正なメモリアクセスをしてしまうことがある。
// std::arrayを使用して、このような問題のないSafeArrayを作り、単体テストを行え。

template <typename T, std::size_t N>
struct SafeArray : std::array<T, N> {
    using std::array<T, N>::array;  // 継承コンストラクタ

    template <typename... ARGS>  // コンストラクタを定義
    SafeArray(ARGS... args) noexcept(std::is_nothrow_constructible_v<T, ARGS...>) : base_type{args...}
    {
    }

    using base_type = std::array<T, N>;
    using size_type = typename base_type::size_type;

    typename base_type::reference       operator[](size_type i) { return this->at(i); }
    typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
};

namespace {
TEST(TemplateMetaProgrammingA, safe_array)
{
    auto sa = SafeArray<int, 3>{1, 2, 3};

    static_assert(std::is_nothrow_constructible_v<decltype(sa), int>);
    ASSERT_EQ(3, sa.size());
    ASSERT_EQ(1, sa[0]);
    ASSERT_EQ(2, sa[1]);
    ASSERT_EQ(3, sa[2]);
    ASSERT_THROW(sa[3], std::out_of_range);

    auto sa2 = SafeArray<std::string, 2>{"1", "2"};

    static_assert(!std::is_nothrow_constructible_v<decltype(sa2), char const*>);
    ASSERT_EQ(2, sa2.size());
    ASSERT_EQ("1", sa2[0]);
    ASSERT_EQ("2", sa2[1]);
    ASSERT_THROW(sa2[2], std::out_of_range);
}
}  // namespace
// @@@ sample end
