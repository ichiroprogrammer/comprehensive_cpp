#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// std::array、std::vector、std::string等のSTLの配列型コンテナはインデックスアクセスに対して、
// レンジのチェックをしないため、不正なメモリアクセスをしてしまうことがある。
// std::arrayを使用して、このような問題のないSafeArrayを作り、単体テストを行え。

namespace {
TEST(TemplateMetaProgrammingQ, safe_array)
{
    // SafeArrayの単体テスト
}
}  // namespace
// @@@ sample end
