#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/command_executor.h"

class TestCommandExecutorState_Idle : public CommandExecutor::State {
public:
    TestCommandExecutorState_Idle();
    std::unique_ptr<CommandExecutor::State> Exec(CommandExecutor::msg_t const& msg) override;
};

class TestCommandExecutorState_WaitingForCompletion : public CommandExecutor::State {
public:
    TestCommandExecutorState_WaitingForCompletion();
    std::unique_ptr<CommandExecutor::State> Exec(CommandExecutor::msg_t const& msg) override;
};

// ### TestCommandExecutorState_Idle
TestCommandExecutorState_Idle::TestCommandExecutorState_Idle()
    : CommandExecutor::State{CommandExecutor::StateSym::Idle}
{
    LOGGER("TestCommandExecutorState_Idle");
}

std::unique_ptr<CommandExecutor::State> TestCommandExecutorState_Idle::Exec(
    CommandExecutor::msg_t const& msg)
{
    LOGGER("Command", CmdId2Sv(msg.id));
    if (msg.id != CommandExecutor::CommandId::Start) {
        return std::unique_ptr<CommandExecutor::State>{};
    }

    if (msg.on_completion) {
        msg.on_completion();
    }
    LOGGER("gen TestCommandExecutorState_WaitingForCompletion !!!!!!!!");
    return std::make_unique<TestCommandExecutorState_WaitingForCompletion>();
}

std::unique_ptr<CommandExecutor::State> TestCommandExecutorState_WaitingForCompletion::Exec(
    CommandExecutor::msg_t const& msg)
{
    if (msg.id != CommandExecutor::CommandId::Complete) {
        return std::unique_ptr<CommandExecutor::State>{};
    }

    if (msg.on_completion) {
        msg.on_completion();
    }
    LOGGER("gen TestCommandExecutorState_Idle !!!!!!!!");
    return std::make_unique<TestCommandExecutorState_Idle>();
}

TestCommandExecutorState_WaitingForCompletion::TestCommandExecutorState_WaitingForCompletion()
    : CommandExecutor::State{CommandExecutor::StateSym::WaitingForCompletion}
{
    LOGGER("TestCommandExecutorState_WaitingForCompletion");
}

TEST(CommandExecutorTest, AAA_FistTest)
{
    LOGGER_INIT("log.txt");  // logging用のファイルの初期化
}

TEST(CommandExecutorTest, TestAsyncCommand)
{
    CommandExecutor executor{std::make_unique<TestCommandExecutorState_Idle>()};
    int             on_completion_couner{};

    ASSERT_EQ(executor.GetState(), CommandExecutor::StateSym::Idle);

    executor.command(CommandExecutor::CommandExecutor::CommandId::Start, [&on_completion_couner]() {
        ++on_completion_couner;
        LOGGER("on complete:");
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 非同期処理の完了を待つ
    ASSERT_EQ(executor.GetState(), CommandExecutor::StateSym::WaitingForCompletion);
    ASSERT_EQ(on_completion_couner, 1);

    executor.command(CommandExecutor::CommandExecutor::CommandId::Complete,
                     [&on_completion_couner]() {
                         ++on_completion_couner;
                         LOGGER("on complete:");
                     });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 非同期処理の完了を待つ
    ASSERT_EQ(executor.GetState(), CommandExecutor::StateSym::Idle);
    ASSERT_EQ(on_completion_couner, 2);

    // Idle状態でCompleteコマンドを受診しても捨てるのでon_completion()は呼び出されない
    executor.command(CommandExecutor::CommandId::Complete, [&on_completion_couner]() {
        ++on_completion_couner;
        LOGGER("on complete:");
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::StateSym::Idle);
    ASSERT_EQ(on_completion_couner, 2);
}
