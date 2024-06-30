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

    CommandExecutor();
    ~CommandExecutor();
    void command(CommandExecutor::MsgId aid, std::function<void()> callback);

    struct msg_t;

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t>              pimpl;
    std::unique_ptr<CommandExecutorState> state;

    std::thread gen_worker();
};

class CommandExecutorState {
public:
    virtual std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) = 0;
    virtual ~CommandExecutorState()                                                       = 0;
};

std::string_view MsgId2Sv(CommandExecutor::MsgId);
