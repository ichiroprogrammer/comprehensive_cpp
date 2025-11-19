#include "gtest_wrapper.h"

#include "scoped_guard.h"

namespace Nstd {
namespace {

// @@@ sample begin 0:0

TEST(ScopedGuard, scoped_guard)
{
    auto a = 0;

    {
        auto sg = ScopedGuard{[&a]() noexcept { a = 99; }};
        ASSERT_NE(99, a);  // ~ScopedGuardは呼ばれていない
    }
    ASSERT_EQ(99, a);  // ~ScopedGuardは呼ばれた
}
// @@@ sample end
}  // namespace
}  // namespace Nstd
