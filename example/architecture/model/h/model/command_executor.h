#pragma once

#include <memory.h>

#include <functional>
#include <string>
#include <string_view>
#include <thread>

class CommandExecutor {
public:
    struct msg_t {
        msg_t() : exec([] {}) {}
        msg_t(std::function<void()> exec) : exec{std::move(exec)} {}
        std::function<void()> exec;
    };

    CommandExecutor();
    ~CommandExecutor();
    bool ExecAsync(std::function<void()> exec);
    bool IsBusy() const noexcept;
    void Sync();

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl_;

    std::thread gen_worker();
};
