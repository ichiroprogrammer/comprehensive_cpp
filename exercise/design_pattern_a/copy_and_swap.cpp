#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
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

    CopyAndSwap(CopyAndSwap const& rhs) : name0_{rhs.name0_}, name1_{rhs.name1_} {}

    CopyAndSwap(CopyAndSwap&& rhs) noexcept : name0_{std::exchange(rhs.name0_, nullptr)}, name1_{std::move(rhs.name1_)}
    {
    }

    CopyAndSwap& operator=(CopyAndSwap const& rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        // copyコンストラクタの使用
        auto tmp = CopyAndSwap{rhs};  // ここでエクセプションが発生しても、tmp以外、壊れない

        Swap(tmp);

        return *this;
    }

    CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
    {
        if (this == &rhs) {
            return *this;
        }

        auto tmp = CopyAndSwap{std::move(rhs)};  // moveコンストラクタ

        Swap(tmp);

        return *this;
    }

    void Swap(CopyAndSwap& rhs) noexcept
    {
        std::swap(name0_, rhs.name0_);
        std::swap(name1_, rhs.name1_);
    }

    char const* GetName0() const noexcept { return name0_; }

    std::string const& GetName1() const noexcept { return name1_; }

    ~CopyAndSwap() = default;

private:
    char const* name0_;
    std::string name1_;
};

#if defined(__clang__)  // clangコンパイルでの警告抑止
#define SUPPRESS_WARN_CLANG_BEGIN _Pragma("clang diagnostic push")
#define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED _Pragma("clang diagnostic ignored \"-Wself-assign-overloaded\"")
#define SUPPRESS_WARN_CLANG_SELF_MOVE _Pragma("clang diagnostic ignored \"-Wself-move\"")
#define SUPPRESS_WARN_CLANG_END _Pragma("clang diagnostic pop")
#else
#define SUPPRESS_WARN_CLANG_BEGIN
#define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED
#define SUPPRESS_WARN_CLANG_SELF_MOVE
#define SUPPRESS_WARN_CLANG_END
#endif

// 本来は下記単体テストは分割すべきだが、紙面の都合上一つにまとめる。
TEST(DesignPatternA, CopyAndSwap)
{
    // test for explicit CopyAndSwap(char const* name0, char const* name1)
    auto n = CopyAndSwap{nullptr, nullptr};
    ASSERT_STREQ("", n.GetName0());
    ASSERT_EQ("", n.GetName1());

    auto a = CopyAndSwap{"a0", "a1"};
    ASSERT_STREQ("a0", a.GetName0());
    ASSERT_EQ("a1", a.GetName1());

    // test for void Swap(CopyAndSwap& rhs) noexcept
    auto b = CopyAndSwap{"b0", "b1"};

    a.Swap(b);
    ASSERT_STREQ("b0", a.GetName0());
    ASSERT_EQ("b1", a.GetName1());
    ASSERT_STREQ("a0", b.GetName0());
    ASSERT_EQ("a1", b.GetName1());

    a.Swap(a);
    ASSERT_STREQ("b0", a.GetName0());
    ASSERT_EQ("b1", a.GetName1());

    // test for CopyAndSwap(CopyAndSwap const& rhs)
    auto const const_a = CopyAndSwap{"const_a0", "const_a1"};

    auto b_copy = CopyAndSwap{const_a};

    ASSERT_STREQ("const_a0", b_copy.GetName0());
    ASSERT_EQ("const_a1", b_copy.GetName1());

    // test for CopyAndSwap& operator=(CopyAndSwap const& rhs)
    auto const c = CopyAndSwap{"c0", "c1"};

    b_copy = c;
    ASSERT_STREQ("c0", b_copy.GetName0());
    ASSERT_EQ("c1", b_copy.GetName1());

    SUPPRESS_WARN_CLANG_BEGIN;
    SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED;

    b_copy = b_copy;

    SUPPRESS_WARN_CLANG_END;

    ASSERT_STREQ("c0", b_copy.GetName0());
    ASSERT_EQ("c1", b_copy.GetName1());

    // test for CopyAndSwap(CopyAndSwap&& rhs) noexcept
    auto b_move = CopyAndSwap{std::move(b)};

    ASSERT_STREQ("a0", b_move.GetName0());
    ASSERT_EQ("a1", b_move.GetName1());

#if !defined(__clang_analyzer__)  // move後のオブジェクトにリードアクセスするとscan-buildでエラー
    ASSERT_EQ(nullptr, b.GetName0());
    ASSERT_EQ("", b.GetName1());
#endif

    auto c_move = CopyAndSwap{std::move(const_a)};  // moveに見えるが実はコピー

    ASSERT_STREQ("const_a0", const_a.GetName0());
    ASSERT_EQ("const_a1", const_a.GetName1());

    ASSERT_STREQ("const_a0", c_move.GetName0());
    ASSERT_EQ("const_a1", c_move.GetName1());

    // test for CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
    c_move = std::move(b_move);
    ASSERT_STREQ("a0", c_move.GetName0());
    ASSERT_EQ("a1", c_move.GetName1());

#if !defined(__clang_analyzer__)  // move後のオブジェクトにリードアクセスするとscan-buildでエラー
    ASSERT_EQ(nullptr, b_move.GetName0());
    ASSERT_EQ("", b_move.GetName1());
#endif

    SUPPRESS_WARN_CLANG_BEGIN;
    SUPPRESS_WARN_CLANG_SELF_MOVE;

    c_move = std::move(c_move);

    SUPPRESS_WARN_CLANG_END;

    ASSERT_STREQ("a0", c_move.GetName0());
    ASSERT_EQ("a1", c_move.GetName1());
}
// @@@ sample end
}  // namespace
