#pragma once
#include <memory.h>

#include <functional>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

class Observer;

class Model {
public:
    class Observer {
    public:
        virtual void Update(Model const& model) = 0;
        virtual ~Observer()                     = default;
    };

    struct msg_t {
        msg_t() : exec([] {}) {}
        msg_t(std::function<void()> exec) : exec{std::move(exec)} {}
        std::function<void()> exec;
    };

    Model();
    ~Model();
    bool ExecAsync(std::function<void()> exec);
    bool IsBusy() const noexcept;
    void Sync();
    void Attach(std::unique_ptr<Observer>&& observer);

private:
    void workerFunction();
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl_;

    std::thread gen_worker();
    void        notify();
};
