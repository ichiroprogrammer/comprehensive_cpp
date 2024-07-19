#pragma once

#include <memory.h>

#include <functional>
#include <string>
#include <string_view>
#include <thread>

class CommandExecutor {
public:
    enum class CommandId { Start, Complete };
    enum class StateSym { Idle, WaitingForCompletion };

    struct msg_t {
        msg_t() : id{CommandExecutor::CommandId::Start}, on_completion([] {}) {}
        msg_t(CommandExecutor::CommandId id, std::function<void()> on_completion)
            : id{id}, on_completion{std::move(on_completion)}
        {
        }

        CommandExecutor::CommandId id;
        std::function<void()>      on_completion;
    };

    class State {
    public:
        State(StateSym state_sym) : state_sym_{state_sym} {}

        StateSym                       GetState() const noexcept { return state_sym_; }
        virtual std::unique_ptr<State> Exec(CommandExecutor::msg_t const& msg) = 0;
        virtual ~State()                                                       = default;

    private:
        StateSym state_sym_;
    };

    CommandExecutor(std::unique_ptr<State>&&);
    ~CommandExecutor();
    void     command(CommandExecutor::CommandId aid, std::function<void()> on_completion);
    StateSym GetState() const noexcept;

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl;

    std::thread gen_worker();
};

class CommandExecutorState_Idle : public CommandExecutor::State {
public:
    CommandExecutorState_Idle();
    std::unique_ptr<CommandExecutor::State> Exec(CommandExecutor::msg_t const& msg) override;
};

class CommandExecutorState_WaitingForCompletion : public CommandExecutor::State {
public:
    CommandExecutorState_WaitingForCompletion();
    std::unique_ptr<CommandExecutor::State> Exec(CommandExecutor::msg_t const& msg) override;
};

std::string_view MsgId2Sv(CommandExecutor::StateSym);
std::string_view CmdId2Sv(CommandExecutor::CommandId);
