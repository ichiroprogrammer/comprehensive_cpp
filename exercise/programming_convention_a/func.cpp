#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <type_traits>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
TEST(ProgrammingConventionFuncA, NonMemberFunc)
{
    // [A]
    // 適切な#includeを追加し、上記のextern宣言がなくとも下記がコンパイルできるようにせよ。

    // このファイルの先頭付近に
    // #include <cmath>
    // を追加した。

    ASSERT_EQ(1, cos(0));
}
// @@@ sample end

// @@@ sample begin 1:0
// [A]
// 下記のクラスAのメンバ関数の不正確な記述を修正せよ。
// また、単体テストを同様に修正せよ。

class A {
public:
    A() : strings_{GetStringsDefault()} {}

    void SetStrings(size_t index, std::string str)
    {
        if (index < max_len) {
            strings_[index] = str;
        }
    }

    std::vector<std::string>&       GetStrings() noexcept { return strings_; }
    std::vector<std::string> const& GetStrings() const noexcept { return strings_; }
    constexpr size_t                MaxLen() const noexcept { return max_len; }

    static std::vector<std::string> const& GetStringsDefault()
    {
        static const std::vector<std::string> strings_default{max_len, ""};
        return strings_default;
    }

private:
    std::vector<std::string> strings_;
    static constexpr size_t  max_len{3};
};

TEST(ProgrammingConventionFuncA, MemberFunc)
{
    auto a = A{};

    auto const& strings_default = a.GetStringsDefault();
    ASSERT_EQ((std::vector<std::string>{a.MaxLen(), ""}), strings_default);

    auto const& strings = a.GetStrings();

    ASSERT_EQ((std::vector<std::string>{a.MaxLen(), ""}), strings);

    a.SetStrings(1, "TEST");
    ASSERT_EQ("", strings[0]);

    // [A]
    // このテストをASSERT_EQでパスできるようにせよ
    ASSERT_EQ("TEST", strings[1]);

    ASSERT_EQ("", strings[2]);

    // 上記は下記のように書くべき
    ASSERT_EQ((std::vector<std::string>{"", "TEST", ""}), strings);
}
// @@@ sample end

// @@@ sample begin 2:0
// [A]
// 下記クラスAutoGenのコンパイラが自動生成するメンバ関数を生成しないようにせよ。

class AutoGen {
public:
    AutoGen()  = delete;
    ~AutoGen() = delete;

    AutoGen(AutoGen const&)                = delete;
    AutoGen& operator=(AutoGen const&)     = delete;
    AutoGen(AutoGen&&) noexcept            = delete;
    AutoGen& operator=(AutoGen&&) noexcept = delete;
};
// @@@ sample end

// @@@ sample begin 3:0
// [A]
// 下記クラスDelConstructorの2つのコンストラクタのコードクローンをできるだけ排除せよ。

class DelConstructor {
public:
    explicit DelConstructor(std::string const& str) : str0_{str + "0"}, str1_{str + "1"}, str2_{str + "2"} {}

    explicit DelConstructor(int32_t num) : DelConstructor{std::to_string(num) + "_"} {}

    std::string const& GetString0() const { return str0_; }
    std::string const& GetString1() const { return str1_; }
    std::string const& GetString2() const { return str2_; }

private:
    std::string const str0_;
    std::string const str1_;
    std::string const str2_;
};

TEST(ProgrammingConventionFuncA, Constructor)
{
    {
        auto const dc = DelConstructor{"hehe"};

        ASSERT_EQ("hehe0", dc.GetString0());
        ASSERT_EQ("hehe1", dc.GetString1());
        ASSERT_EQ("hehe2", dc.GetString2());
    }
    {
        auto const dc = DelConstructor{123};

        ASSERT_EQ("123_0", dc.GetString0());
        ASSERT_EQ("123_1", dc.GetString1());
        ASSERT_EQ("123_2", dc.GetString2());
    }
}
// @@@ sample end

// @@@ sample begin 4:0
// [A]
// 下記クラスIngeter、IntegerHolderに適切にcopyコンストラクタ、copy代入演算子を追加して、
// 単体テストを行え。
class Integer {
public:
    explicit Integer(int32_t i) noexcept : i_{i} {}

    Integer(Integer const& rhs) noexcept = default;

    Integer& operator=(Integer const& rhs) noexcept = default;

    int32_t GetValue() const noexcept { return i_; }

private:
    int32_t i_;
};

class IntegerHolder {
public:
    explicit IntegerHolder(int32_t i) : integer_{std::make_unique<Integer>(i)} {}

    IntegerHolder(IntegerHolder const& rhs) : integer_{std::make_unique<Integer>(*rhs.integer_)} {}

    IntegerHolder& operator=(IntegerHolder const& rhs)
    {
        *integer_ = *(rhs.integer_);
        return *this;
    }

    int32_t GetValue() const noexcept { return integer_->GetValue(); }

private:
    std::unique_ptr<Integer> integer_;
};

TEST(ProgrammingConventionFuncA, Constructor2)
{
    {
        auto i = Integer{3};
        ASSERT_EQ(3, i.GetValue());

        auto j = Integer{i};
        ASSERT_EQ(3, j.GetValue());

        auto k = Integer{0};
        ASSERT_EQ(0, k.GetValue());

        k = i;
        ASSERT_EQ(3, k.GetValue());
    }
    {
        auto i = IntegerHolder{3};
        ASSERT_EQ(3, i.GetValue());

        auto j = IntegerHolder{i};
        ASSERT_EQ(3, j.GetValue());

        auto k = IntegerHolder{0};
        ASSERT_EQ(0, k.GetValue());

        k = i;
        ASSERT_EQ(3, k.GetValue());
    }
}
// @@@ sample end

// @@@ sample begin 5:0
// [A]
// 上記問題を解決したIntegerHolderにmoveコンストラクタ、move演算子を追加した
// クラスIntegerHolder2を作成し、単体テストを行え。

class IntegerHolder2 {
public:
    explicit IntegerHolder2(int32_t i) : integer_{std::make_unique<Integer>(i)} {}

    IntegerHolder2(IntegerHolder2 const& rhs) : integer_{std::make_unique<Integer>(*rhs.integer_)} {}

    IntegerHolder2(IntegerHolder2&& rhs) noexcept : integer_{std::move(rhs.integer_)} {}

    IntegerHolder2& operator=(IntegerHolder2 const& rhs) noexcept
    {
        *integer_ = *(rhs.integer_);
        return *this;
    }

    IntegerHolder2& operator=(IntegerHolder2&& rhs) noexcept
    {
        integer_ = std::move(rhs.integer_);
        return *this;
    }

    int32_t GetValue() const
    {
        if (!integer_) {
            throw std::bad_exception{};
        }
        return integer_->GetValue();
    }

private:
    std::unique_ptr<Integer> integer_;
};

#ifndef __clang_analyzer__
TEST(ProgrammingConventionFuncA, Move)
{
    {
        auto i = IntegerHolder2{3};
        auto j = IntegerHolder2{std::move(i)};

        ASSERT_EQ(3, j.GetValue());

        ASSERT_THROW(i.GetValue(), std::bad_exception);
    }
    {
        auto i = IntegerHolder2{30};
        auto j = IntegerHolder2{0};

        ASSERT_EQ(0, j.GetValue());

        j = std::move(i);

        ASSERT_EQ(30, j.GetValue());

        ASSERT_THROW(i.GetValue(), std::bad_exception);
    }
}
#endif
// @@@ sample end

// @@@ sample begin 6:0
// [A]
// 下記PrimeNumbersは引数で与えられた整数以下の素数を返す関数である。
// PrimeNumbersの単体テストを作成し、その後、行数を短くする等のリファクタリングを行え。

namespace {
uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
{
    for (auto i = 2 * curr_prime_num; i < is_num_prime.size(); i += curr_prime_num) {
        is_num_prime[i] = false;  // 次の倍数は素数ではない
    }

    auto prime_num = curr_prime_num;

    do {  // 次の素数の探索
        ++prime_num;
    } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

    return prime_num;
}
}  // namespace

std::vector<uint32_t> PrimeNumbers(uint32_t max_number)
{
    auto result = std::vector<uint32_t>{};

    if (max_number < 2) {  // ガード節。2未満の素数はない。
        return result;
    }

    auto prime_num    = 2U;                                       // 最初の素数
    auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
    is_num_prime[0] = is_num_prime[1] = false;

    do {
        result.emplace_back(prime_num);
        prime_num = next_prime_num(prime_num, is_num_prime);
    } while (prime_num < is_num_prime.size());

    return result;
}

TEST(ProgrammingConventionFuncA, Lines)
{
    ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(0));
    ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(1));
    ASSERT_EQ((std::vector<uint32_t>{2}), PrimeNumbers(2));
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), PrimeNumbers(3));
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7}), PrimeNumbers(8));
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), PrimeNumbers(30));
}
// @@@ sample end

// @@@ sample begin 7:0
// [A]
// 下記クラスBase、Derivedの単体テストを完成せよ。

class Base {
public:
    virtual ~Base() = default;
    int32_t f() noexcept { return 0; }

    virtual int32_t g() noexcept { return 0; }
};

class Derived : public Base {
public:
    int32_t f() noexcept { return 1; }

    virtual int32_t g() noexcept override { return 1; }
};

TEST(ProgrammingConventionFuncA, Overload)
{
    auto  b     = Base{};
    auto  d     = Derived{};
    Base& d_ref = d;

    ASSERT_EQ(0, b.f());
    ASSERT_EQ(0, b.g());

    ASSERT_EQ(1, d.f());
    ASSERT_EQ(1, d.g());

    ASSERT_EQ(0, d_ref.f());
    ASSERT_EQ(1, d_ref.g());
}
// @@@ sample end

// @@@ sample begin 8:0
// [A]
// 下記関数Squareは、引数が浮動小数点となることを想定していない。
// 誤用を防ぐために、引数に浮動小数点を指定された場合、コンパイルできないようにせよ。
int32_t Square(int32_t a) noexcept { return a * a; }
int32_t Square(double a) noexcept = delete;

TEST(ProgrammingConventionFuncA, Overload2)
{
    ASSERT_EQ(9, Square(3));
#if 0  // int32_t Square(double a) = delete;により下記はコンパイルできない。
    ASSERT_EQ(4, Square(2.5));
#endif
}
// @@@ sample end

// @@@ sample begin 9:0
// [A]
// 下記AddStringsの仮引数等を適切に修正せよ。
using Strings = std::list<std::string>;
Strings AddStrings(Strings const& a, Strings const* b)
{
    auto ret = a;

    if (b == nullptr) {
        return ret;
    }

    ret.insert(ret.end(), b->begin(), b->end());

    return ret;
}

TEST(ProgrammingConventionFuncA, Parameter)
{
    auto a = Strings{"abc", "d"};
    auto b = Strings{"e", "fgh", "i"};

    auto ret = AddStrings(a, nullptr);
    ASSERT_EQ(ret, (Strings{"abc", "d"}));

    ret = AddStrings(a, &b);
    ASSERT_EQ(ret, (Strings{"abc", "d", "e", "fgh", "i"}));

    ASSERT_EQ(AddStrings(a, nullptr), (Strings{"abc", "d"}));

    ASSERT_EQ(AddStrings(a, &b), (Strings{"abc", "d", "e", "fgh", "i"}));
}
// @@@ sample end

// @@@ sample begin 10:0
// [A]
// 下記Factorialをconstexpr関数にせよ。
constexpr uint32_t Factorial(uint32_t a) noexcept
{
    if (a == 0 || a == 1) {
        return 1;
    }

    return Factorial(a - 1) * a;
}

TEST(ProgrammingConventionFuncA, ConstexprFunc)
{
    static_assert(1 == Factorial(0), "Factorial fail");
    ASSERT_EQ(1, Factorial(0));
    ASSERT_EQ(6, Factorial(3));
    ASSERT_EQ(120, Factorial(5));
    ASSERT_EQ(3628800, Factorial(10));
}
// @@@ sample end

}  // namespace
