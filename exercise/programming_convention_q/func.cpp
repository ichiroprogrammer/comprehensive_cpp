#include <list>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
extern "C" double cos(double x);

TEST(ProgrammingConventionFuncQ, NonMemberFunc)
{
    // [Q]
    // 適切な#includeを追加し、上記のextern宣言がなくとも下記がコンパイルできるようにせよ。
    ASSERT_EQ(1, cos(0));
}
// @@@ sample end

namespace {
// @@@ sample begin 1:0
// [Q]
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

    std::vector<std::string>& GetStrings() { return strings_; }
    std::vector<std::string>  GetStrings() const { return strings_; }
    size_t                    MaxLen() { return max_len; }

    std::vector<std::string>& GetStringsDefault()
    {
        static auto strings_default = std::vector<std::string>{max_len, ""};
        return strings_default;
    }

private:
    std::vector<std::string> strings_;
    static constexpr size_t  max_len{3};
};

TEST(ProgrammingConventionFuncQ, MemberFunc)
{
    auto a = A{};

    auto strings_default = a.GetStringsDefault();
    ASSERT_EQ("", strings_default[0]);
    ASSERT_EQ("", strings_default[1]);
    ASSERT_EQ("", strings_default[2]);
    ASSERT_EQ(3, a.MaxLen());

    auto strings = a.GetStrings();

    ASSERT_EQ("", strings[0]);
    ASSERT_EQ("", strings[1]);
    ASSERT_EQ("", strings[2]);

    a.SetStrings(1, "TEST");
    ASSERT_EQ("", strings[0]);

    // [Q]
    // このテストをASSERT_EQでパスできるようにせよ
    ASSERT_NE("TEST", strings[1]);

    ASSERT_EQ("", strings[2]);
}
// @@@ sample end

// @@@ sample begin 2:0
// [Q]
// 下記クラスAutoGenのコンパイラが自動生成するメンバ関数を生成しないようにせよ。

class AutoGen {};
// @@@ sample end

// @@@ sample begin 3:0
// [Q]
// 下記クラスDelConstructorの2つのコンストラクタのコードクローンをできるだけ排除せよ。
// また、不正確な記述を修正せよ。

class DelConstructor {
public:
    DelConstructor(std::string const& str) : str0_{str + "0"}, str1_{str + "1"}, str2_{str + "2"} {}

    DelConstructor(int32_t num)
        : str0_{std::to_string(num) + "_0"},
          str1_{std::to_string(num) + "_1"},
          str2_{std::to_string(num) + "_2"}
    {
    }

    std::string& GetString0() { return str0_; }
    std::string& GetString1() { return str1_; }
    std::string& GetString2() { return str2_; }

private:
    std::string str0_;
    std::string str1_;
    std::string str2_;
};

TEST(ProgrammingConventionFuncQ, Constructor)
{
    {
        auto dc = DelConstructor{"hehe"};

        ASSERT_EQ("hehe0", dc.GetString0());
        ASSERT_EQ("hehe1", dc.GetString1());
        ASSERT_EQ("hehe2", dc.GetString2());
    }
    {
        auto dc = DelConstructor{123};

        ASSERT_EQ("123_0", dc.GetString0());
        ASSERT_EQ("123_1", dc.GetString1());
        ASSERT_EQ("123_2", dc.GetString2());
    }
}
// @@@ sample end

// @@@ sample begin 4:0
// [Q]
// 下記クラスIngeter、IntegerHolderに適切にcopyコンストラクタ、copy代入演算子を追加して、
// 単体テストを行え(DISABLED_削除)。
class Integer {
public:
    explicit Integer(int32_t i) noexcept : i_{i} {}

    int32_t GetValue() const noexcept { return i_; }

private:
    int32_t i_;
};

class IntegerHolder {
public:
    explicit IntegerHolder(int32_t i) : integer_{new Integer{i}} {}

    int32_t GetValue() const noexcept { return integer_->GetValue(); }

    ~IntegerHolder() { delete integer_; }

private:
    Integer* integer_;
};

#ifndef __clang_analyzer__
TEST(DISABLED_ProgrammingConventionFuncQ, Constructor2)
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
#endif
// @@@ sample end

// @@@ sample begin 5:0
// [Q]
// 上記問題を解決したIntegerHolderにmoveコンストラクタ、move演算子を追加した
// クラスIntegerHolder2を作成し、単体テストを行え。
// @@@ sample end

// @@@ sample begin 6:0
// [Q]
// 下記PrimeNumbersは引数で与えられた整数以下の素数を返す関数である。
// PrimeNumbersの単体テストを作成し、その後、行数を短くする等のリファクタリングを行え。

std::vector<uint32_t> PrimeNumbers(uint32_t max_number)
{
    auto result = std::vector<uint32_t>{};

    if (max_number >= 2) {
        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);

            for (auto i = 2 * prime_num; i < is_num_prime.size(); i += prime_num) {
                is_num_prime[i] = false;
            }

            do {  // 次の素数の探索
                ++prime_num;
            } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

        } while (prime_num < is_num_prime.size());

        return result;
    }
    else {
        return result;
    }
}

TEST(ProgrammingConventionFuncQ, Lines)
{
    ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(0));
    // 以下に単体テストを追加
}
// @@@ sample end

// @@@ sample begin 7:0
// [Q]
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

TEST(ProgrammingConventionFuncQ, Overload)
{
    auto  b     = Base{};
    auto  d     = Derived{};
    Base& d_ref = d;

#if 0
    // 下記?は0もしくは1が入る
    ASSERT_EQ(?, b.f());
    ASSERT_EQ(?, b.g());

    ASSERT_EQ(?, d.f());
    ASSERT_EQ(?, d.g());

    ASSERT_EQ(?, d_ref.f());
    ASSERT_EQ(?, d_ref.g());
#endif
}
// @@@ sample end

// @@@ sample begin 8:0
// [Q]
// 下記関数Squareは、引数が浮動小数点となることを想定していない。
// 誤用を防ぐために、引数に浮動小数点を指定された場合、コンパイルできないようにせよ。
int32_t Square(int32_t a) noexcept { return a * a; }

TEST(ProgrammingConventionFuncQ, Overload2)
{
    ASSERT_EQ(9, Square(3));
    ASSERT_EQ(4, Square(2.5));  // この誤用を防ぐためにコンパイルエラーにせよ。
}
// @@@ sample end

// @@@ sample begin 9:0
// [Q]
// 下記AddStringsの仮引数等を適切に修正せよ。
using Strings = std::list<std::string>;
void AddStrings(Strings a, Strings* b, Strings* ret)
{
    *ret = a;

    if (b == nullptr) {
        return;
    }

    ret->insert(ret->end(), b->begin(), b->end());
}

TEST(ProgrammingConventionFuncQ, Parameter)
{
    auto a = Strings{"abc", "d"};
    auto b = Strings{"e", "fgh", "i"};

    auto ret = Strings{};
    AddStrings(a, nullptr, &ret);
    ASSERT_EQ(ret, (Strings{"abc", "d"}));

    AddStrings(a, &b, &ret);
    ASSERT_EQ(ret, (Strings{"abc", "d", "e", "fgh", "i"}));
}
// @@@ sample end

// @@@ sample begin 10:0
// [Q]
// 下記Factorialをconstexpr関数にせよ。
uint32_t Factorial(uint32_t a) noexcept
{
    if (a == 0 || a == 1) {
        return 1;
    }

    auto fact = 1U;

    for (auto i = 2U; i <= a; ++i) {
        fact *= i;
    }

    return fact;
}

TEST(ProgrammingConventionFuncQ, ConstexprFunc)
{
#if 0  // Factorialはconstexpr関数でないため、下記はコンパイルできない。
    static_assert(1 == Factorial(0), "Factorial fail");
#endif
    ASSERT_EQ(1, Factorial(0));
    ASSERT_EQ(6, Factorial(3));
    ASSERT_EQ(120, Factorial(5));
    ASSERT_EQ(3628800, Factorial(10));
}
// @@@ sample end

}  // namespace
