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
#include "model/x.h"

struct CommandExecutor::pimpl_t {
    pimpl_t(std::thread&& th) : worker{std::move(th)} {}

    std::list<CommandExecutor::msg_t> msgs{};
    std::mutex                        msg_mtx{};
    std::condition_variable           msg_cv{};

    std::atomic<bool> busy = false;

    std::thread       worker;
    std::atomic<bool> stop = false;
};

std::thread CommandExecutor::gen_worker()
{
    return std::thread{&CommandExecutor::workerFunction, this};
}

// ###
CommandExecutor::CommandExecutor()
    : pimpl_{std::make_unique<CommandExecutor::pimpl_t>(gen_worker())}
{
}

CommandExecutor::~CommandExecutor()
{
    pimpl_->stop = true;
    pimpl_->busy = false;
    pimpl_->msg_cv.notify_one();
    pimpl_->worker.join();
}

bool CommandExecutor::IsBusy() const noexcept { return pimpl_->busy; }

void CommandExecutor::Sync()
{
    for (;;) {
        if (!pimpl_->busy) {
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool CommandExecutor::ExecAsync(std::function<void()> exec)
{
    if (pimpl_->busy) {
        return false;
    }

    {
        std::unique_lock<std::mutex> lock{pimpl_->msg_mtx};
        pimpl_->msgs.push_back({exec});
        pimpl_->busy = true;
    }
    pimpl_->msg_cv.notify_one();

    return true;
}

void CommandExecutor::workerFunction()
{
    for (;;) {
        msg_t msg;
        {
            std::unique_lock<std::mutex> lock{pimpl_->msg_mtx};
            pimpl_->msg_cv.wait(
                lock, [&pimpl_ = *pimpl_] { return !pimpl_.msgs.empty() || pimpl_.stop; });
            if (pimpl_->stop && pimpl_->msgs.empty()) {
                return;
            }

            msg = std::move(pimpl_->msgs.front());
            pimpl_->msgs.pop_front();
        }

        msg.exec();
        pimpl_->busy = false;

        LOGGER("Processing message");
    }
}
