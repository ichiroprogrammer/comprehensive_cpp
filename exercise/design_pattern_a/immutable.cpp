#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記クラスPrimeNumbersはSetMaxNumberにより状態が変わってしまうことがある。
// 状態変更が必要ない場合、こういった仕様はない方が良い。
// PrimeNumbersからSetMaxNumberを削除し、このクラスをimmutableにせよ。

// [解説]
// * Immutableなクラスとは、生成後状態が変えられないクラスである。
// * PrimeNumbersをImmutableにするには
//      * SetMaxNumberを廃止し、メンバ変数をconstにする。
//      * GeneratePrimeNumbersをconstメンバ関数にして、GetPrimeNumbersに変更する。
//      * copy代入演算子を =deleteする(これがなくてもconstメンバならばコピーはできないが)

class PrimeNumbers {
public:
    explicit PrimeNumbers(uint32_t max_number = 2);

    PrimeNumbers(PrimeNumbers const&)            = default;
    PrimeNumbers& operator=(PrimeNumbers const&) = delete;  // constメンバはコピーできない。

    uint32_t                     GetMaxNumber() const noexcept { return max_number_; }
    std::vector<uint32_t> const& GetPrimeNumbers() const noexcept { return prime_numbers_; }

private:
    uint32_t const              max_number_;
    std::vector<uint32_t> const prime_numbers_{};

    static uint32_t              next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept;
    static std::vector<uint32_t> get_prime_numbers(uint32_t max_number);
};

uint32_t PrimeNumbers::next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
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

std::vector<uint32_t> PrimeNumbers::get_prime_numbers(uint32_t max_number)
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

PrimeNumbers::PrimeNumbers(uint32_t max_number) : max_number_{max_number}, prime_numbers_{get_prime_numbers(max_number)}
{
}

TEST(DesignPatternA, Immutable)
{
    auto pm1 = PrimeNumbers{1};
    ASSERT_EQ((std::vector<uint32_t>{}), pm1.GetPrimeNumbers());

    auto pm3 = PrimeNumbers{3};
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3.GetPrimeNumbers());

    auto pm30 = PrimeNumbers{30};
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm30.GetPrimeNumbers());

    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm30.GetPrimeNumbers());

    auto pm3_copy = PrimeNumbers{pm3};
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3_copy.GetPrimeNumbers());

#if 0  // immutableなのでコピーはできない。
    auto pm  = PrimeNumbers{1};
    auto pm5 = PrimeNumbers{5};
    pm       = pm5;
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5}), pm.GetPrimeNumbers());
#endif
}
// @@@ sample end
}  // namespace
