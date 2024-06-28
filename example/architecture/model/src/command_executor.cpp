#include <thread>
#include <list>
#include <iterator>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <string>
#include <cstring>

#include "model/command_executor.h"

struct CommandExecutor::msg_t  {
    msg_t() : str{}, on_completion([]{}) {}
    msg_t(std::string const& str, std::function<void()> on_completion) 
        : on_completion(std::move(on_completion)) 
    {
        auto const  length = std::min(str.length(), std::size(msg_t::str)-1);
        std::strncpy(this->str, str.c_str(), length);
        this->str[length] = '\0';
    }

    char str[12];
    std::function<void()> on_completion;
};

struct CommandExecutor::pimpl_t {
    pimpl_t(std::thread&& th) : worker{std::move(th)} {}
    std::list<CommandExecutor::msg_t> messages {};
    std::mutex mutex{};
    std::condition_variable cv{};
    std::thread worker;
    bool stop = false;
};

std::thread CommandExecutor::gen_worker()
{
    return std::thread{&CommandExecutor::workerFunction, this};
}

CommandExecutor::CommandExecutor()
    : pimpl{ std::make_unique<CommandExecutor::pimpl_t>(gen_worker())} { }

CommandExecutor::~CommandExecutor() {
    {
        std::unique_lock<std::mutex> lock{pimpl->mutex};
        pimpl->stop = true;
    }
    pimpl->cv.notify_one();
    pimpl->worker.join();
}

void CommandExecutor::command(const std::string& content, std::function<void()> on_completion) {
    {
        std::unique_lock<std::mutex> lock{pimpl->mutex};
        pimpl->messages.push_back({content, on_completion});
    }
    pimpl->cv.notify_one();
}

void CommandExecutor::workerFunction()
{
    for(;;) {
        msg_t msg;
        {
            std::unique_lock<std::mutex> lock{pimpl->mutex};
            pimpl->cv.wait(lock, [this] { return !pimpl->messages.empty() || pimpl->stop; });
            if (pimpl->stop && pimpl->messages.empty()) {return;}

            msg = std::move(pimpl->messages.front());
            pimpl->messages.pop_front();
        }

        std::cout << "Processing message: " << msg.str << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Message processed." << std::endl;
        if (msg.on_completion) {
            msg.on_completion();
        }
    }
}
