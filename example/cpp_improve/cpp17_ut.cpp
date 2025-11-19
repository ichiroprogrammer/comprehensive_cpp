#include <cstdint>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "gtest_wrapper.h"

#include "nstd_type2str.h"
#include "suppress_warning.h"

namespace {

TEST(cpp17, uniform_init)
{
    // @@@ sample begin 0:0

#if 1  // C++17からリストによる直接初期化の型推論の規則が変更された
    auto a0 = {0};
    auto a1 = {0, 1};
    auto a2{0};

    static_assert(std::is_same_v<decltype(a0), std::initializer_list<int>>);
    static_assert(std::is_same_v<decltype(a1), std::initializer_list<int>>);
    static_assert(std::is_same_v<decltype(a2), int>);
#else
    auto ill_formd0 = {0, 1.0};  // ill-formed: int と double からは推論できない
    auto ill_formd0{0, 1};       // C++17からill-formd
#endif
    // @@@ sample end
    IGNORE_UNUSED_VAR(a0, a1, a2);
}

// @@@ sample begin 1:0

struct alignas(64) AlignedStruct {  // C++17 newのアライメント指定
    int x;
};

// @@@ sample end

TEST(cpp17, align_new)
{
    // @@@ sample begin 1:1

    AlignedStruct* ptr = new AlignedStruct;

    ASSERT_EQ(reinterpret_cast<std::uintptr_t>(ptr) % 64, 0);  // アライメントの確認

    delete ptr;
    // @@@ sample end
}

TEST(cpp17, if_with_vale_define) {}
}  // namespace

// @@@ sample begin 2:0

namespace org {
struct custom_iterator {  // カスタムイテレータの定義
    int const* ptr;

    custom_iterator(int const* p) : ptr(p) {}
    bool             operator!=(custom_iterator const& other) const { return ptr != other.ptr; }
    int const&       operator*() const { return *ptr; }
    custom_iterator& operator++()
    {
        ++ptr;
        return *this;
    }
};

int const* begin(std::vector<int> const& vec)
{
    return vec.data();  // 通常のポインタを返す
}

// 配列の終端はカスタムイテレータを返すend関数
custom_iterator end(std::vector<int> const& vec)
{
    return custom_iterator(vec.data() + vec.size());  // カスタムイテレータを返す
}

struct vec_int : std::vector<int> {};
}  // namespace org
// @@@ sample end

namespace {
TEST(cpp17, string_view_range)
{
    // @@@ sample begin 2:1

    org::vec_int       nums{{1, 2, 3, 4, 5}};
    std::ostringstream os;

    // std::begin<T>, std::end<T>の戻り型が異なることの証明
    static_assert(!std::is_same_v<decltype(org::begin(nums)), decltype(org::end(nums))>);

    for (int num : nums) {  // 範囲for文でポインタとカスタムイテレータの不一致を許容
        os << num << " ";
    }

    ASSERT_EQ("1 2 3 4 5 ", os.str());
    // @@@ sample end
}

// @@@ sample begin 3:0

struct MyStruct {
    int value = 42;

    auto getValue()
    {
        return [*this]() { return value; };  // *thisをコピーキャプチャ
    }
};
// @@@ sample end

TEST(cpp17, lambda_this)
{
    // @@@ sample begin 3:1

    MyStruct obj;
    auto     lambda = obj.getValue();
    obj.value       = 0;  // コピーキャプチャされたため、影響を受けない

    ASSERT_EQ(lambda(), 42);  // コピーキャプチャの影響で元の値が保持される
    // @@@ sample end
}

}  // namespace
