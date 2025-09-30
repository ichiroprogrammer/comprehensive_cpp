#include <atomic>
#include <future>

#include "gtest_wrapper.h"

#include "do_heavy_algorithm.h"
#include "lib.h"

namespace {

#ifdef __CYGWIN__  // cygwinでは、std::threadがバグっている
#define RefAsyncR6_Opt DISABLED_RefAsyncR6
#else  // __linux__
#define RefAsyncR6_Opt RefAsyncR6
#endif

// @@@ sample begin 0:0

TEST(RefAsyncR6, surrogate_task0)
{
    auto& dispatcher = Dispatcher::Inst();
    auto  result     = 0;
    auto  pre_task   = []() noexcept { return 99; };
    auto  post_task  = [&result](int&& t) noexcept { result = t; };

    auto st = MakeTwoPhaseTaskPtr(pre_task, post_task);

    dispatcher.Invoke(std::move(st));  // 委譲タスク登録
    dispatcher.Stop();                 // ExecUntilStopを終了させるタスクの登録
    dispatcher.ExecUntilStop();        // 全タスクの実行

    ASSERT_EQ(99, result);  // pre_taskの戻り値をpost_taskがresultへセット
}
// @@@ sample end

TEST(RefAsyncR6_Opt, surrogate_task1)
{
    auto& dispatcher = Dispatcher::Inst();
    auto  result     = 0;
    auto  st         = MakeTwoPhaseTaskPtr(
        []() noexcept {
            org_msec_sleep(200);
            return 3;
        },
        [&result](int const& t) noexcept { result = t; });

    dispatcher.Invoke(std::move(st));

    dispatcher.Stop();
    dispatcher.ExecUntilStop();

    ASSERT_EQ(3, result);
}

TEST(RefAsyncR6_Opt, surrogate_task2)
{
    auto& dispatcher = Dispatcher::Inst();
    auto  result     = 0;
    auto  st         = MakeTwoPhaseTaskPtr(
        []() noexcept {
            org_msec_sleep(200);
            return 3;
        },
        [&result](int const& t) noexcept { result = t; });

    dispatcher.Invoke(std::move(st));

    auto result2 = std::string{};
    auto st2     = MakeTwoPhaseTaskPtr([] { return do_heavy_algorithm("haha"); },
                                   [&result2](std::string&& t) noexcept { result2 = std::move(t); });
    dispatcher.Invoke(std::move(st2));

    auto result3 = std::string{};
    auto st3     = MakeTwoPhaseTaskPtr([] { return do_heavy_algorithm("hehe"); },
                                   [&result3](std::string&& t) noexcept { result3 = std::move(t); });
    dispatcher.Invoke(std::move(st3));

    auto fu = std::async(std::launch::async, [&dispatcher] { dispatcher.ExecUntilStop(); });

    dispatcher.Stop();

    fu.wait();

    ASSERT_EQ(3, result);
    ASSERT_EQ("HAHA", result2);
}
}  // namespace
