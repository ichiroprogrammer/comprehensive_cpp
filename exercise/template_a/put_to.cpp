#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// 下記のように名前空間TemplateMP、エイリアスInts_tとそのoperator<<が定義されている場合、
// 単体テストで示した通り、Ints_tのoperator<<を使用するためには、
// 名前空間による修飾やusing宣言/ディレクティブの記述が必要になる。
// Ints_tをstd::vectorから継承したクラスとして定義することにより、このような記述を不要にせよ。

namespace TemplateMP {

struct Ints_t : std::vector<int> {
    using std::vector<int>::vector;  // 継承コンストラクタ
};

std::ostream& operator<<(std::ostream& os, Ints_t const& ints)
{
    auto first = true;
    for (auto i : ints) {
        if (!std::exchange(first, false)) {
            os << " : ";
        }
        os << i;
    }

    return os;
}
}  // namespace TemplateMP

namespace {
TEST(TemplateMetaProgrammingA, put_to)
{
    {
        auto oss  = std::ostringstream{};
        auto ints = TemplateMP::Ints_t{1, 2, 3};

        oss << ints;  // ADLによるname lookup

        ASSERT_EQ("1 : 2 : 3", oss.str());
    }
}
}  // namespace
// @@@ sample end
