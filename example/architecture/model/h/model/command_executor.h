#pragma once

#include <memory.h>

#include <functional>
#include <string>
#include <string_view>
#include <thread>

class CommandExecutorState;

class CommandExecutor {
public:
    enum class MsgId { Idle, SeqStep1, SeqStep2 };

    CommandExecutor(std::unique_ptr<CommandExecutorState>&&);
    ~CommandExecutor();
    void command(CommandExecutor::MsgId aid, std::function<void()> callback);

    struct msg_t {
        msg_t() : id{CommandExecutor::MsgId::Idle}, on_completion([] {}) {}
        msg_t(CommandExecutor::MsgId id, std::function<void()> on_completion)
            : id{id}, on_completion{std::move(on_completion)}
        {
        }

        CommandExecutor::MsgId id;
        std::function<void()>  on_completion;
    };

    MsgId GetState() const noexcept;

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
    virtual CommandExecutor::MsgId                GetState() const noexcept               = 0;
    virtual ~CommandExecutorState()                                                       = default;
};

std::string_view MsgId2Sv(CommandExecutor::MsgId);
