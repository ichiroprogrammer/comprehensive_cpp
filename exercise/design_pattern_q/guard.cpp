#include <optional>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 以下の関数PrimeNumbersをガード節や、関数の括りだし等によってリファクタリングせよ。

std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_number)
{
    if (max_number < 65536) {  // 演算コストが高いためエラーにする
        auto result = std::vector<uint32_t>{};

        if (max_number >= 2) {
            auto prime_num    = 2U;                                       // 最初の素数
            auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない
            is_num_prime[0] = is_num_prime[1] = false;

            do {
                result.emplace_back(prime_num);

                for (auto i = 2 * prime_num; i < is_num_prime.size(); i += prime_num) {
                    is_num_prime[i] = false;  // 次の倍数は素数ではない
                }

                do {  // 次の素数の探索
                    ++prime_num;
                } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

            } while (prime_num < is_num_prime.size());
        }
        return result;
    }

    return std::nullopt;
}

TEST(DesignPatternQ, Guard)
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
