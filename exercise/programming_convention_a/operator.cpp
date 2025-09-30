#include <memory>

#include "gtest_wrapper.h"

#include "suppress_warning.h"

namespace {
// @@@ sample begin 0:0
// [A]
// 下記whichのif文を三項演算子を使用して書き直せ。
int32_t which(bool left, int32_t lhs, int32_t rhs) noexcept { return left ? lhs : rhs; }

TEST(ProgrammingConventionOperatorA, OoOperator)
{
    ASSERT_EQ(3, which(true, 3, 4));
    ASSERT_EQ(4, which(false, 3, 4));
}
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 下記DeleteProblemのメモリ管理の問題を修正せよ。
// また、他の問題があれば、合わせて修正せよ。
class DeleteProblem {
public:
    DeleteProblem(char const* str0 = nullptr, char const* str1 = nullptr)
        : str0_{(str0 == nullptr) ? std::unique_ptr<std::string>{} : std::make_unique<std::string>(str0)},
          str1_{(str1 == nullptr) ? std::unique_ptr<std::string>{} : std::make_unique<std::string>(str1)}
    {
    }

    DeleteProblem(DeleteProblem const&)            = delete;
    DeleteProblem& operator=(DeleteProblem const&) = delete;

    std::string const* GetStr0() const noexcept { return str0_.get(); }
    std::string const* GetStr1() const noexcept { return str1_.get(); }

private:
    std::unique_ptr<std::string> str0_;
    std::unique_ptr<std::string> str1_;
};

TEST(ProgrammingConventionOperatorA, Delete)
{
    {
        auto const dp = DeleteProblem{};

        ASSERT_EQ(nullptr, dp.GetStr0());
        ASSERT_EQ(nullptr, dp.GetStr1());
    }
    {
        auto const dp = DeleteProblem{"abc"};

        ASSERT_EQ("abc", *dp.GetStr0());
        ASSERT_EQ(nullptr, dp.GetStr1());
    }
    {
        auto const dp = DeleteProblem{"abc", "de"};

        ASSERT_EQ("abc", *dp.GetStr0());
        ASSERT_EQ("de", *dp.GetStr1());
    }
}
// @@@ sample end

SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_SIZEOF_ARRAY_ARG;

// @@@ sample begin 2:0
// [A]
// 下記Size1() - Size4()の単体テストを作れ。
size_t Size0(int32_t a) noexcept { return sizeof(a); }

size_t Size1(int32_t a[10]) noexcept { return sizeof(a); }

size_t Size2(int32_t a[]) noexcept { return sizeof(a); }

size_t Size3(int32_t* a) noexcept { return sizeof(a); }

size_t Size4(int32_t (&a)[10]) noexcept { return sizeof(a); }

TEST(ProgrammingConventionOperatorA, Sizeof)
{
    int32_t array[10]{};

    ASSERT_EQ(4, Size0(array[0]));
    ASSERT_EQ(sizeof(void*), Size1(array));
    ASSERT_EQ(sizeof(void*), Size2(array));
    ASSERT_EQ(sizeof(void*), Size3(array));
    ASSERT_EQ(sizeof(int32_t) * 10, Size4(array));
}
// @@@ sample end
SUPPRESS_WARN_END;

// @@@ sample begin 3:0
// [A]
// 下記クラスX、Y、ZとGetNameをdynamic_castを使わずに書き直せ。

class X {
public:
    virtual std::string GetName() const { return "X"; }

    virtual ~X() = default;
};

class Y : public X {
public:
    virtual std::string GetName() const override { return "Y"; }
};

class Z : public X {
public:
    virtual std::string GetName() const override { return "Z"; }
};

std::string GetName(X const& x) { return x.GetName(); }

TEST(ProgrammingConventionOperatorA, Cast)
{
    auto x = X{};
    auto y = Y{};
    auto z = Z{};

    ASSERT_EQ("X", GetName(x));
    ASSERT_EQ("Y", GetName(y));
    ASSERT_EQ("Z", GetName(z));
}
// @@@ sample end

}  // namespace
