#pragma once

#include <memory.h>

#include <functional>
#include <string>
#include <string_view>
#include <thread>

class CommandExecutorState;

class CommandExecutor {
public:
    enum class CommandId { Start, Complete };
    enum class State { Idle, WaitingForCompletion };

    CommandExecutor(std::unique_ptr<CommandExecutorState>&&);
    ~CommandExecutor();
    void command(CommandExecutor::CommandId aid, std::function<void()> on_completion);

    struct msg_t {
        msg_t() : id{CommandExecutor::CommandId::Start}, on_completion([] {}) {}
        msg_t(CommandExecutor::CommandId id, std::function<void()> on_completion)
            : id{id}, on_completion{std::move(on_completion)}
        {
        }

        CommandExecutor::CommandId id;
        std::function<void()>      on_completion;
    };

    State GetState() const noexcept;

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl;

    std::thread gen_worker();
};

class CommandExecutorState {
public:
    CommandExecutorState()                                                                = default;
    virtual std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) = 0;
    virtual CommandExecutor::State                GetState() const noexcept               = 0;
    virtual ~CommandExecutorState()                                                       = default;
};

std::string_view MsgId2Sv(CommandExecutor::State);
std::string_view CmdId2Sv(CommandExecutor::CommandId);
