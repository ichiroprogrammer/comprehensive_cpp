#include <optional>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 以下の関数PrimeNumbersをガード節や、関数の括りだし等によってリファクタリングせよ。

inline uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
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

inline std::vector<uint32_t> prime_numbers(uint32_t max_number)
{
    auto result       = std::vector<uint32_t>{};
    auto prime_num    = 2U;                                       // 最初の素数
    auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない
    is_num_prime[0] = is_num_prime[1] = false;

    do {
        result.emplace_back(prime_num);
        prime_num = next_prime_num(prime_num, is_num_prime);
    } while (prime_num < is_num_prime.size());

    return result;
}

std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_number)
{
    if (max_number >= 65536) {  // ガード節。演算コストが高いためエラーにする
        return std::nullopt;
    }

    if (max_number < 2) {  // ガード節。2未満の素数はない
        return std::vector<uint32_t>{};
    }

    return prime_numbers(max_number);
}

TEST(DesignPatternA, Guard)
{
    auto result = PrimeNumbers(1);
    ASSERT_TRUE(result);
    ASSERT_EQ((std::vector<uint32_t>{}), *result);

    result = PrimeNumbers(2);
    ASSERT_TRUE(result);
    ASSERT_EQ((std::vector<uint32_t>{2}), *result);

    result = PrimeNumbers(30);
    ASSERT_TRUE(result);
    ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), *result);

    ASSERT_FALSE(PrimeNumbers(65536));
}
// @@@ sample end
}  // namespace
