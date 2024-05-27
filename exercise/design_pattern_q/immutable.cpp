#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスPrimeNumbersはSetMaxNumberにより状態が変わってしまうことがある。
// 状態変更が必要ない場合、こういった仕様はない方が良い。
// PrimeNumbersからSetMaxNumberを削除し、このクラスをimmutableにせよ。

class PrimeNumbers {
public:
    PrimeNumbers() = default;

    PrimeNumbers(PrimeNumbers const&)            = default;
    PrimeNumbers& operator=(PrimeNumbers const&) = default;

    uint32_t GetMaxNumber() const noexcept { return max_number_; }
    void     SetMaxNumber(uint32_t max_number) noexcept
    {
        if (max_number != max_number_) {
            cached_     = false;
            max_number_ = max_number;
        }
    }

    std::vector<uint32_t> const& GeneratePrimeNumbers();

private:
    uint32_t              max_number_{0};
    bool                  cached_{false};
    std::vector<uint32_t> prime_numbers_{};

    static uint32_t              next_prime_num(uint32_t           curr_prime_num,
                                                std::vector<bool>& is_num_prime) noexcept;
    static std::vector<uint32_t> get_prime_numbers(uint32_t max_number);
};

uint32_t PrimeNumbers::next_prime_num(uint32_t           curr_prime_num,
                                      std::vector<bool>& is_num_prime) noexcept
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
    auto result       = std::vector<uint32_t>{};
    auto prime_num    = 2U;                                       // 最初の素数
    auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
    is_num_prime[0] = is_num_prime[1] = false;

    do {
        result.emplace_back(prime_num);
        prime_num = next_prime_num(prime_num, is_num_prime);
    } while (prime_num < is_num_prime.size());

    return result;
}

std::vector<uint32_t> const& PrimeNumbers::GeneratePrimeNumbers()
{
    if (cached_) {
        return prime_numbers_;
    }

    if (max_number_ < 2) {  // ガード節。2未満の素数はない。
        prime_numbers_.clear();
    }
    else {
        prime_numbers_ = get_prime_numbers(max_number_);
    }

    cached_ = true;
    return prime_numbers_;
}

TEST(DesignPatternQ, Immutable)
{
    auto pm = PrimeNumbers{};

    pm.SetMaxNumber(1);
    ASSERT_EQ((std::vector<uint32_t>{}), pm.GeneratePrimeNumbers());

    pm.SetMaxNumber(3);
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GeneratePrimeNumbers());

    pm.SetMaxNumber(30);
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}),
              pm.GeneratePrimeNumbers());

    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}),
              pm.GeneratePrimeNumbers());

    pm.SetMaxNumber(3);
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GeneratePrimeNumbers());

    auto pm3_copy = PrimeNumbers{pm};
    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3_copy.GeneratePrimeNumbers());

    auto pm5 = PrimeNumbers{};
    pm5.SetMaxNumber(5);
    pm = pm5;
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5}), pm.GeneratePrimeNumbers());
}
// @@@ sample end
}  // namespace
