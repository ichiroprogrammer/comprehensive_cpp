#include "gtest_wrapper.h"

#include "controller.h"
#include "model.h"
#include "suppress_warning.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR3, Controller)
{
    auto model = Model{};
    auto controller = Controller{model};  // オブジェクト生成程度の単体テストしかできない
    IGNORE_UNUSED_VAR(controller);  // @@@ delete
}
// @@@ sample end
}  // namespace
