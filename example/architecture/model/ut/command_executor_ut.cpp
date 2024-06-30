#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/command_executor.h"

TEST(CommandExecutorTest, TestAsyncCommand)
{
    CommandExecutor executor;
    bool            callbackCalled = false;

    executor.command(CommandExecutor::MsgId::SeqStep1, [&callbackCalled]() {
        callbackCalled = true;
        std::cout << "on complete !!!!" << std::endl;
    });

    // 非同期処理の完了を待つ
    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_TRUE(callbackCalled);
}
