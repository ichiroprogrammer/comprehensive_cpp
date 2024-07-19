#include <thread>

#include "gtest/gtest.h"
#include "model/x.h"

TEST(SlowMoverTest, TestAsyncCommand)
{
    X    executor;
    bool callbackCalled = false;

    executor.command([&callbackCalled]() { callbackCalled = true; });

    // 非同期処理の完了を待つ
    std::this_thread::sleep_for(std::chrono::seconds(3));

    EXPECT_TRUE(callbackCalled);
}
