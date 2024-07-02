#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/command_executor.h"

class TestCommandExecutorState_SeqStep2 : public CommandExecutorState {
public:
    TestCommandExecutorState_SeqStep2()
    {
        std::cout << "TestCommandExecutorState_SeqStep2" << std::endl;
    }
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override;

    CommandExecutor::MsgId GetState() const noexcept override
    {
        return CommandExecutor::MsgId::SeqStep2;
    }
};

class TestCommandExecutorState_SeqStep1 : public CommandExecutorState {
public:
    TestCommandExecutorState_SeqStep1()
    {
        std::cout << "TestCommandExecutorState_SeqStep1" << std::endl;
    }
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override
    {
        if (msg.id != CommandExecutor::MsgId::SeqStep2) {
            return std::unique_ptr<CommandExecutorState>{};
        }

        std::cout << "gen TestCommandExecutorState_SeqStep2 !!!!!!!!" << std::endl;
        return std::make_unique<TestCommandExecutorState_SeqStep2>();
    }

    CommandExecutor::MsgId GetState() const noexcept override
    {
        return CommandExecutor::MsgId::SeqStep1;
    }
};

class TestCommandExecutorState_Idle : public CommandExecutorState {
public:
    TestCommandExecutorState_Idle() { std::cout << "TestCommandExecutorState_Idle" << std::endl; }
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override
    {
        if (msg.id != CommandExecutor::MsgId::SeqStep1) {
            return std::unique_ptr<CommandExecutorState>{};
        }

        std::cout << "gen TestCommandExecutorState_SeqStep1 !!!!!!!!" << std::endl;
        return std::make_unique<TestCommandExecutorState_SeqStep1>();
    }

    CommandExecutor::MsgId GetState() const noexcept override
    {
        return CommandExecutor::MsgId::Idle;
    }
};

std::unique_ptr<CommandExecutorState> TestCommandExecutorState_SeqStep2::Exec(
    CommandExecutor::msg_t const& msg)
{
    if (msg.id != CommandExecutor::MsgId::Idle) {
        return std::unique_ptr<CommandExecutorState>{};
    }
    std::cout << "gen TestCommandExecutorState_Idle !!!!!!!!" << std::endl;
    return std::make_unique<TestCommandExecutorState_Idle>();
}

TEST(CommandExecutorTest, TestAsyncCommand)
{
    CommandExecutor executor{std::make_unique<TestCommandExecutorState_Idle>()};
    int             on_completion_couner{};

    std::this_thread::sleep_for(std::chrono::seconds(1));  // 非同期処理の完了を待つ
    ASSERT_EQ(executor.GetState(), CommandExecutor::MsgId::Idle);

    executor.command(CommandExecutor::MsgId::SeqStep1, [&on_completion_couner]() {
        ++on_completion_couner;
        std::cout << "on complete:" << on_completion_couner << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::MsgId::SeqStep1);
    ASSERT_EQ(on_completion_couner, 1);

    executor.command(CommandExecutor::MsgId::SeqStep2, [&on_completion_couner]() {
        ++on_completion_couner;
        std::cout << "on complete:" << on_completion_couner << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::MsgId::SeqStep2);
    ASSERT_EQ(on_completion_couner, 2);

    //
    executor.command(CommandExecutor::MsgId::Idle, [&on_completion_couner]() {
        ++on_completion_couner;
        std::cout << "on complete:" << on_completion_couner << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));  // 非同期処理の完了を待つ

    ASSERT_EQ(executor.GetState(), CommandExecutor::MsgId::Idle);
    ASSERT_EQ(on_completion_couner, 3);
}
