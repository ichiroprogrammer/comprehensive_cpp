#include "gtest_wrapper.h"

#include "class.h"
#include "header.h"
#include "lib/inc/xxx.h"
#include "preprocessor.h"

namespace {

TEST(ProgrammingConvention, forward_decl)
{
    // @@@ sample begin 0:0

    // Pod0, Pod1の定義がなくても宣言があるためコンパイルできる
    forward_decl(nullptr, nullptr);

    // 下記のソースコードのコンパイルには、Pod0の定義が必要なのでコンパイルできない
    // forward_decl(nullptr);
    // @@@ sample end
}
}  // namespace
