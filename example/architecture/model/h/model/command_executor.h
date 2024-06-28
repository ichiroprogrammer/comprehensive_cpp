#pragma once

#include <memory.h>

#include <functional>
#include <string>
#include <thread>

class CommandExecutor {
public:
    CommandExecutor();
    ~CommandExecutor();
    void command(const std::string& content, std::function<void()> callback);

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl;
    struct msg_t;

    std::thread gen_worker();
};
