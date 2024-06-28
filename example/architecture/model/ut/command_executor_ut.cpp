#include "gtest/gtest.h"

#include "model/command_executor.h"
#include "logging/logger.h"

TEST(CommandExecutorTest, TestAsyncCommand) {
    CommandExecutor executor;
    bool callbackCalled = false;

    executor.command("Test message", [&callbackCalled]() {
        callbackCalled = true;
    });

    // 非同期処理の完了を待つ
    std::this_thread::sleep_for(std::chrono::seconds(3));

    EXPECT_TRUE(callbackCalled);
}
