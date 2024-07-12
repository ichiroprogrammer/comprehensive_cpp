#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/command_executor.h"

class CommandExecutorState_WaitingForCompletion : public CommandExecutorState {
public:
    CommandExecutorState_WaitingForCompletion()
    {
        LOGGER("CommandExecutorState_WaitingForCompletion");
    }
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override;

    CommandExecutor::State GetState() const noexcept override
    {
        return CommandExecutor::State::WaitingForCompletion;
    }
};

class CommandExecutorState_Idle : public CommandExecutorState {
public:
    CommandExecutorState_Idle() { LOGGER("CommandExecutorState_Idle"); }
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override
    {
        LOGGER("Command", CmdId2Sv(msg.id));
        if (msg.id != CommandExecutor::CommandId::Start) {
            return std::unique_ptr<CommandExecutorState>{};
        }

        LOGGER("gen CommandExecutorState_WaitingForCompletion !!!!!!!!");
        return std::make_unique<CommandExecutorState_WaitingForCompletion>();
    }

    CommandExecutor::State GetState() const noexcept override
    {
        return CommandExecutor::State::Idle;
    }
};

std::unique_ptr<CommandExecutorState> CommandExecutorState_WaitingForCompletion::Exec(
    CommandExecutor::msg_t const& msg)
{
    if (msg.id != CommandExecutor::CommandId::Complete) {
        return std::unique_ptr<CommandExecutorState>{};
    }

    LOGGER("gen CommandExecutorState_Idle !!!!!!!!");
    return std::make_unique<CommandExecutorState_Idle>();
}

TEST(CommandExecutorTest, AAA_FistTest)
{
    LOGGER_INIT("log.txt");  // logging用のファイルの初期化
}

TEST(CommandExecutorTest, TestAsyncCommand)
{
    CommandExecutor executor{std::make_unique<CommandExecutorState_Idle>()};
    int             on_completion_couner{};

    ASSERT_EQ(executor.GetState(), CommandExecutor::State::Idle);

    executor.command(CommandExecutor::CommandExecutor::CommandId::Start, [&on_completion_couner]() {
        ++on_completion_couner;
        LOGGER("on complete:");
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    executor.command(CommandExecutor::CommandExecutor::CommandId::Complete,
                     [&on_completion_couner]() {
                         ++on_completion_couner;
                         LOGGER("on complete:");
                     });
    ASSERT_EQ(executor.GetState(), CommandExecutor::State::WaitingForCompletion);
    ASSERT_EQ(on_completion_couner, 1);

    executor.command(CommandExecutor::CommandId::Complete, [&on_completion_couner]() {
        ++on_completion_couner;
        LOGGER("on complete:");
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::State::Idle);
    ASSERT_EQ(on_completion_couner, 2);

    //
    executor.command(CommandExecutor::CommandId::Complete, [&on_completion_couner]() {
        ++on_completion_couner;
        LOGGER("on complete:");
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::State::Idle);
    ASSERT_EQ(on_completion_couner, 3);
}
