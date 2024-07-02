#include <condition_variable>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include "model/command_executor.h"

struct CommandExecutor::pimpl_t {
    pimpl_t(std::thread&& th, std::unique_ptr<CommandExecutorState>&& state)
        : worker{std::move(th)}, state{std::move(state)}
    {
    }
    std::list<CommandExecutor::msg_t>     messages{};
    std::mutex                            mutex_stop{};
    std::mutex                            mutex_state{};
    std::condition_variable               cv{};
    std::thread                           worker;
    bool                                  stop = false;
    std::unique_ptr<CommandExecutorState> state;
};

std::thread CommandExecutor::gen_worker()
{
    return std::thread{&CommandExecutor::workerFunction, this};
}

// ###

class CommandExecutorState_Idle : CommandExecutorState {
public:
    std::unique_ptr<CommandExecutorState> Exec(CommandExecutor::msg_t const& msg) override
    {
        if (msg.id == CommandExecutor::MsgId::Idle) {
        }
        return std::unique_ptr<CommandExecutorState>{};
    }

    CommandExecutor::MsgId GetState() const noexcept override
    {
        return CommandExecutor::MsgId::Idle;
    }
};

// ##
CommandExecutor::CommandExecutor(std::unique_ptr<CommandExecutorState>&& state)
    : pimpl{std::make_unique<CommandExecutor::pimpl_t>(gen_worker(), std::move(state))}
{
}

CommandExecutor::MsgId CommandExecutor::GetState() const noexcept
{
    std::unique_lock<std::mutex> lock{pimpl->mutex_state};

    return pimpl->state->GetState();
}

CommandExecutor::~CommandExecutor()
{
    {
        std::unique_lock<std::mutex> lock{pimpl->mutex_stop};
        pimpl->stop = true;
    }
    pimpl->cv.notify_one();
    pimpl->worker.join();
}

void CommandExecutor::command(CommandExecutor::MsgId id, std::function<void()> on_completion)
{
    {
        std::unique_lock<std::mutex> lock{pimpl->mutex_stop};
        pimpl->messages.push_back({id, on_completion});
    }
    pimpl->cv.notify_one();
}

void CommandExecutor::workerFunction()
{
    for (;;) {
        msg_t msg;
        {
            std::unique_lock<std::mutex> lock{pimpl->mutex_stop};
            pimpl->cv.wait(lock, [this] { return !pimpl->messages.empty() || pimpl->stop; });
            if (pimpl->stop && pimpl->messages.empty()) {
                return;
            }

            msg = std::move(pimpl->messages.front());
            pimpl->messages.pop_front();
        }

        std::cout << "Processing message: " << MsgId2Sv(msg.id) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        std::cout << "Message processed." << std::endl;

        std::cout << "Current State:" << MsgId2Sv(pimpl->state->GetState()) << std::endl;
        auto next = pimpl->state->Exec(msg);
        if (next) {
            pimpl->state = std::move(next);
        }

        if (msg.on_completion) {
            msg.on_completion();
        }
    }
}

namespace {
struct id2sv {
    CommandExecutor::MsgId id;
    std::string_view       sv;
};

id2sv table[]{{CommandExecutor::MsgId::Idle, std::string_view{"Idle"}},
              {CommandExecutor::MsgId::SeqStep1, std::string_view{"SeqStep1"}},
              {CommandExecutor::MsgId::SeqStep2, std::string_view{"SeqStep2"}}};
}  // namespace

std::string_view MsgId2Sv(CommandExecutor::MsgId id)
{
    for (auto const& e : table) {
        if (e.id == id) {
            return e.sv;
        }
    }

    return std::string_view{"None"};
}
