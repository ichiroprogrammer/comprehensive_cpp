#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスPrimeNumbersはAccessorの多用により、クラスのカプセル化が破壊されている例である。
// これにより、このクラスは凝集性が低く、誤用を誘発しやすい。
// この問題を解決するため、クラスPrimeNumbersや関数GetPrimeNumbersを修正せよ。
// また、別の問題があれば合わせて修正せよ。

class PrimeNumbers {
public:
    uint32_t GetMaxNumber() const { return max_number_; }
    void     SetMaxNumber(uint32_t max_number) { max_number_ = max_number; }
    bool     HasCache() const { return cached_; }
    void     Cashed(bool cached) { cached_ = cached; }

    std::vector<uint32_t>& GetPrimeNumbers() { return prime_numbers_; }

private:
    uint32_t              max_number_;
    bool                  cached_;
    std::vector<uint32_t> prime_numbers_;
};

inline uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime)
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

inline std::vector<uint32_t> get_prime_numbers(uint32_t max_number)
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

void GetPrimeNumbers(PrimeNumbers& pm)
{
    if (pm.HasCache()) {
        return;
    }

    if (pm.GetMaxNumber() < 2) {  // ガード節。2未満の素数はない。
        pm.GetPrimeNumbers().clear();
        return;
    }

    pm.GetPrimeNumbers() = get_prime_numbers(pm.GetMaxNumber());
}

TEST(DesignPatternQ, Accessor)
{
    auto pm = PrimeNumbers{};

    pm.SetMaxNumber(1);
    pm.Cashed(false);
    GetPrimeNumbers(pm);
    pm.Cashed(true);

    ASSERT_EQ((std::vector<uint32_t>{}), pm.GetPrimeNumbers());

    pm.SetMaxNumber(3);
    pm.Cashed(false);
    GetPrimeNumbers(pm);
    pm.Cashed(true);

    ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GetPrimeNumbers());

    pm.SetMaxNumber(30);
    pm.Cashed(false);
    GetPrimeNumbers(pm);
    pm.Cashed(true);

    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GetPrimeNumbers());

    pm.SetMaxNumber(3);
    GetPrimeNumbers(pm);  // pm.Cashed(false);しないので前のまま。
                          // このような用途は考えづらいので、おそらく仕様のバグ。

    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GetPrimeNumbers());
}
// @@@ sample end
}  // namespace
