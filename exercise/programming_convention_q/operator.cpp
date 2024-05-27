#include <cassert>

#include "gtest_wrapper.h"

namespace {
// @@@ sample begin 0:0
// [Q]
// 下記whichのif文を三項演算子を使用して書き直せ。
int32_t which(bool left, int32_t lhs, int32_t rhs) noexcept
{
    if (left) {
        return lhs;
    }
    else {
        return rhs;
    }
}

TEST(ProgrammingConventionOperatorQ, OoOperator)
{
    ASSERT_EQ(3, which(true, 3, 4));
    ASSERT_EQ(4, which(false, 3, 4));
}
// @@@ sample end

// @@@ sample begin 1:0
// [Q]
// 下記DeleteProblemのメモリ管理の問題を修正し、単体テストを行え(DISABLED_削除)。
// また、他の問題があれば、合わせて修正せよ。
class DeleteProblem {
public:
    DeleteProblem(char const* str0 = nullptr, char const* str1 = nullptr)
    {
        if (str0 != nullptr) {
            str0_ = new std::string{str0};
        }
        if (str1 != nullptr) {
            str1_ = new std::string{str1};
        }
    }

    std::string const* GetStr0() { return str0_; }
    std::string const* GetStr1() { return str1_; }

    ~DeleteProblem()
    {
        delete_str(str0_);
        delete_str(str1_);
    }

private:
    static void delete_str(void* str)
    {
        if (str != nullptr) {
            delete str;
        }
    }

    std::string* str0_ = nullptr;
    std::string* str1_ = nullptr;
};

TEST(DISABLED_ProgrammingConventionOperatorQ, Delete)
{
    // この単体テストはメモリリークを起こす
    // このメモリリークはmake san-utで検出される
    {
        auto dp = DeleteProblem{};

        ASSERT_EQ(nullptr, dp.GetStr0());
        ASSERT_EQ(nullptr, dp.GetStr1());
    }
    {
        auto dp = DeleteProblem{"abc"};

        ASSERT_EQ("abc", *dp.GetStr0());
        ASSERT_EQ(nullptr, dp.GetStr1());
    }
    {
        auto dp = DeleteProblem{"abc", "de"};

        ASSERT_EQ("abc", *dp.GetStr0());
        ASSERT_EQ("de", *dp.GetStr1());
    }
}
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 下記Size1() - Size4()の単体テストを作れ。
size_t Size0(int32_t a) noexcept { return sizeof(a); }

size_t Size1(int32_t a[10]) noexcept { return sizeof(a); }

size_t Size2(int32_t a[]) noexcept { return sizeof(a); }

size_t Size3(int32_t* a) noexcept { return sizeof(a); }

size_t Size4(int32_t (&a)[10]) noexcept { return sizeof(a); }

TEST(ProgrammingConventionOperatorQ, Sizeof)
{
    int32_t array[10]{};

    // Size1() - Size4()の単体テスト
    ASSERT_EQ(sizeof(void*), Size3(array));
}
// @@@ sample end

// @@@ sample begin 3:0
// [Q]
// 下記クラスX、Y、ZとGetNameをdynamic_castを使わずに書き直せ。

class X {
public:
    virtual ~X() = default;
};

class Y : public X {};

class Z : public X {};

std::string GetName(X* x)
{
    if (dynamic_cast<Y*>(x) != nullptr) {
        return "Y";
    }
    if (dynamic_cast<Z*>(x) != nullptr) {
        return "Z";
    }
    if (dynamic_cast<X*>(x) != nullptr) {
        return "X";
    }

    assert(false);
    return "UnKnown";
}

TEST(ProgrammingConventionOperatorQ, Cast)
{
    auto x = X{};
    auto y = Y{};
    auto z = Z{};

    ASSERT_EQ("X", GetName(&x));
    ASSERT_EQ("Y", GetName(&y));
    ASSERT_EQ("Z", GetName(&z));
}
// @@@ sample end

}  // namespace
