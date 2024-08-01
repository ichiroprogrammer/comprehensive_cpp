#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/command_executor.h"

TEST(CommandExecutorTest, AAA_FistTest)
{
    LOGGER_INIT("log.txt");  // logging用のファイルの初期化
}

TEST(CommandExecutorTest, ExecAsync)
{
    CommandExecutor executor{};
    int             exec_counter{};

    ASSERT_FALSE(executor.IsBusy());

    executor.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });

    ASSERT_TRUE(executor.IsBusy());

    ASSERT_FALSE(executor.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    }));

    executor.Sync();
    ASSERT_EQ(exec_counter, 1);

    executor.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });

    ASSERT_TRUE(executor.IsBusy());
    executor.Sync();
    ASSERT_EQ(exec_counter, 2);
    ASSERT_FALSE(executor.IsBusy());
}
