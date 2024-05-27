
#include "gtest_wrapper.h"

#include "lib.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR2, Model)
{
    auto model = Model{};  // Modelのデザインが悪いために適切な単体テストは書けない

    model.ConvertStoreAsync("hehe");
}

TEST(RefAsyncR2, dispatch)
{
    auto model = Model{};

    {
        auto exit_code = dispatch(model, "+abc");
        ASSERT_FALSE(exit_code);
    }
    {
        auto exit_code = dispatch(model, "+defg");
        ASSERT_FALSE(exit_code);
    }
    {
        auto exit_code = dispatch(model, ".");
        ASSERT_FALSE(exit_code);
    }
    {
        auto exit_code = dispatch(model, "+hijkl");
        ASSERT_FALSE(exit_code);
    }
    {
        auto exit_code = dispatch(model, "=");
        ASSERT_TRUE(exit_code);
        ASSERT_EQ(0, *exit_code);
    }
    {
        auto exit_code = dispatch(model, "?");
        ASSERT_TRUE(exit_code);
        ASSERT_NE(0, *exit_code);
    }
}
// @@@ sample end
}  // namespace
