#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 以下のクラスCopyAndSwapの
//  * copyコンストラクタ
//  * copy代入演算子
//  * moveコンストラクタ
//  * move代入演算子
// をCopy-And-Swapイデオムを使用して実装し、単体テストを行え。

class CopyAndSwap final {
public:
    explicit CopyAndSwap(char const* name0, char const* name1)
        : name0_{name0 == nullptr ? "" : name0}, name1_{name1 == nullptr ? "" : name1}
    {
    }

    CopyAndSwap(CopyAndSwap const& rhs)
    {
        // この関数の実装
    }

    CopyAndSwap(CopyAndSwap&& rhs) noexcept
    {
        // この関数の実装
    }

    CopyAndSwap& operator=(CopyAndSwap const& rhs)
    {
        // この関数の実装
        return *this;
    }

    CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
    {
        // この関数の実装
        return *this;
    }

    void Swap(CopyAndSwap& rhs) noexcept
    {
        // この関数の実装
    }

    char const* GetName0() const noexcept { return name0_; }

    std::string const& GetName1() const noexcept { return name1_; }

    ~CopyAndSwap() = default;

private:
    char const* name0_;
    std::string name1_;
};

TEST(DesignPatternQ, CopyAndSwap)
{
    // test for explicit CopyAndSwap(char const* name0, char const* name1)
    auto n = CopyAndSwap{nullptr, nullptr};
    ASSERT_STREQ("", n.GetName0());
    ASSERT_EQ("", n.GetName1());

    auto a = CopyAndSwap{"a0", "a1"};
    ASSERT_STREQ("a0", a.GetName0());
    ASSERT_EQ("a1", a.GetName1());
}
// @@@ sample end
}  // namespace
