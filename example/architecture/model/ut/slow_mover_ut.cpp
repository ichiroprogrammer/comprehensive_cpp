#include <thread>

#include "gtest/gtest.h"
#include "model/slow_mover.h"

TEST(SlowMoverTest, TestAsyncCommand)
{
    SlowMover executor;
    bool      callbackCalled = false;

    executor.command([&callbackCalled]() { callbackCalled = true; });

    // 非同期処理の完了を待つ
    std::this_thread::sleep_for(std::chrono::seconds(3));

    EXPECT_TRUE(callbackCalled);
}
