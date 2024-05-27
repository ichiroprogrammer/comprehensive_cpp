#include <memory>

#include "gtest_wrapper.h"

#include "lib.h"
#include "scoped_guard.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR1, dispatch)
{
    auto actual = std::vector<std::string>{};

    {
        auto thd = std::thread{[] {}};                   // NullObject & RAII
        auto sg  = ScopedGuard{[&thd] { thd.join(); }};  // RAII

        {
            auto exit_code = dispatch(thd, actual, "+abc");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(thd, actual, "+defg");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(thd, actual, ".");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(thd, actual, "+hijkl");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(thd, actual, "=");
            ASSERT_TRUE(exit_code);
            ASSERT_EQ(0, *exit_code);
        }
        {
            auto exit_code = dispatch(thd, actual, "?");
            ASSERT_TRUE(exit_code);
            ASSERT_NE(0, *exit_code);
        }
    }

    ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), actual);
}
// @@@ sample end
}  // namespace
