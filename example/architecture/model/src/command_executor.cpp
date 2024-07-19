#include <atomic>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include "logging/logger.h"
#include "model/command_executor.h"

struct CommandExecutor::pimpl_t {
    pimpl_t(std::thread&& th, std::unique_ptr<CommandExecutor::State>&& state)
        : worker{std::move(th)}, state{std::move(state)}
    {
    }
    std::list<CommandExecutor::msg_t>       messages{};
    std::mutex                              mutex_msg{};
    std::mutex                              mutex_state{};
    std::condition_variable                 cv{};
    std::thread                             worker;
    std::atomic<bool>                       stop = false;
    std::unique_ptr<CommandExecutor::State> state;
};

std::thread CommandExecutor::gen_worker()
{
    return std::thread{&CommandExecutor::workerFunction, this};
}

CommandExecutor::StateSym CommandExecutor::GetState() const noexcept
{
    std::unique_lock<std::mutex> lock{pimpl->mutex_state};

    return pimpl->state->GetState();
}

// ### CommandExecutorState_Idle
CommandExecutorState_Idle::CommandExecutorState_Idle()
    : CommandExecutor::State{CommandExecutor::StateSym::Idle}
{
    LOGGER("CommandExecutorState_Idle");
}

std::unique_ptr<CommandExecutor::State> CommandExecutorState_Idle::Exec(
    CommandExecutor::msg_t const& msg)
{
    LOGGER("Command", CmdId2Sv(msg.id));
    if (msg.id != CommandExecutor::CommandId::Start) {
        return std::unique_ptr<CommandExecutor::State>{};
    }

    LOGGER("gen CommandExecutorState_WaitingForCompletion !!!!!!!!");
    return std::make_unique<CommandExecutorState_WaitingForCompletion>();
}

std::unique_ptr<CommandExecutor::State> CommandExecutorState_WaitingForCompletion::Exec(
    CommandExecutor::msg_t const& msg)
{
    if (msg.id != CommandExecutor::CommandId::Complete) {
        return std::unique_ptr<CommandExecutor::State>{};
    }

    LOGGER("gen CommandExecutorState_Idle !!!!!!!!");
    return std::make_unique<CommandExecutorState_Idle>();
}

CommandExecutorState_WaitingForCompletion::CommandExecutorState_WaitingForCompletion()
    : CommandExecutor::State{CommandExecutor::StateSym::WaitingForCompletion}
{
    LOGGER("CommandExecutorState_WaitingForCompletion");
}

// ###
CommandExecutor::CommandExecutor(std::unique_ptr<CommandExecutor::State>&& state)
    : pimpl{std::make_unique<CommandExecutor::pimpl_t>(gen_worker(), std::move(state))}
{
}

CommandExecutor::~CommandExecutor()
{
    pimpl->stop = true;
    pimpl->cv.notify_one();
    pimpl->worker.join();
}

void CommandExecutor::command(CommandExecutor::CommandId id, std::function<void()> on_completion)
{
    {
        std::unique_lock<std::mutex> lock{pimpl->mutex_msg};
        pimpl->messages.push_back({id, on_completion});
    }
    pimpl->cv.notify_one();
}

void CommandExecutor::workerFunction()
{
    for (;;) {
        msg_t msg;
        {
            std::unique_lock<std::mutex> lock{pimpl->mutex_msg};
            pimpl->cv.wait(lock, [this] { return !pimpl->messages.empty() || pimpl->stop; });
            if (pimpl->stop && pimpl->messages.empty()) {
                return;
            }

            msg = std::move(pimpl->messages.front());
            pimpl->messages.pop_front();
        }

        LOGGER("Processing message", CmdId2Sv(msg.id));
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        LOGGER("Message processed", MsgId2Sv(pimpl->state->GetState()));

        if (auto next = pimpl->state->Exec(msg)) {
            std::unique_lock<std::mutex> lock{pimpl->mutex_state};
            pimpl->state = std::move(next);
        }

        if (msg.on_completion) {
            msg.on_completion();
        }
    }
}

std::string_view MsgId2Sv(CommandExecutor::StateSym state)
{
    struct state2sv {
        CommandExecutor::StateSym state;
        std::string_view          sv;
    } table_id2sv[]{{CommandExecutor::StateSym::Idle, std::string_view{"Idle"}},
                    {CommandExecutor::StateSym::WaitingForCompletion,
                     std::string_view{"WaitingForCompletion"}}};

    for (auto const& e : table_id2sv) {
        if (e.state == state) {
            return e.sv;
        }
    }

    return std::string_view{"None"};
}

std::string_view CmdId2Sv(CommandExecutor::CommandId id)
{
    struct cmd_id2sv {
        CommandExecutor::CommandId id;
        std::string_view           sv;
    } cmd_id2sv[]{{CommandExecutor::CommandId::Start, std::string_view{"Start"}},
                  {CommandExecutor::CommandId::Complete, std::string_view{"Complete"}}};

    for (auto const& e : cmd_id2sv) {
        if (e.id == id) {
            return e.sv;
        }
    }

    return std::string_view{"None"};
}
