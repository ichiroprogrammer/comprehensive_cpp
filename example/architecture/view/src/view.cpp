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
#include "view/view.h"

namespace {
char const* b2str(bool b) { return b ? "true" : "false"; }
}  // namespace
struct View::pimpl_t {
    pimpl_t(std::thread&& th) : worker{std::move(th)} {}
    std::list<std::string>  msgs{};
    std::mutex              msg_mtx{};
    std::condition_variable msg_cv{};

    std::condition_variable sync_cv{};
    std::mutex              busy_mtx{};
    bool                    busy = false;

    std::thread       worker;
    std::atomic<bool> stop = false;
};

View::View(std::ostream& ostream)
    : ostream_{ostream}, pimpl_{std::make_unique<View::pimpl_t>(gen_worker())}
{
}

View::~View()
{
    pimpl_->stop = true;
    pimpl_->msg_cv.notify_one();
    pimpl_->worker.join();
}

std::thread View::gen_worker() { return std::thread{&View::worker_function, this}; }

void View::ShowAsync(std::string&& msg)
{
    LOGGER("busy", b2str(pimpl_->busy));
    {
        std::unique_lock<std::mutex> lock{pimpl_->busy_mtx};
        pimpl_->msgs.push_back(std::move(msg));
        pimpl_->busy = true;
    }
    LOGGER("busy", b2str(pimpl_->busy));
    pimpl_->msg_cv.notify_one();
}

void View::Sync()
{
    for (;;) {
        {
            std::unique_lock<std::mutex> lock{pimpl_->busy_mtx};
            pimpl_->sync_cv.wait(lock, [&pimpl = *pimpl_] {
                LOGGER("busy", b2str(pimpl.busy));
                return !pimpl.busy;
            });
        }
        break;
    }
}

void View::show_msg(std::string const& msg)
{
    ostream_ << msg;
    pimpl_->busy = false;
    pimpl_->sync_cv.notify_one();
}

void View::worker_function()
{
    for (;;) {
        {
            std::unique_lock<std::mutex> lock{pimpl_->msg_mtx};
            pimpl_->msg_cv.wait(lock,
                                [&pimpl = *pimpl_] { return !pimpl.msgs.empty() || pimpl.stop; });
            if (pimpl_->stop && pimpl_->msgs.empty()) {
                return;
            }

            std::string msg = std::move(pimpl_->msgs.front());

            LOGGER("Processing message", msg, ":busy", b2str(pimpl_->busy));
            pimpl_->msgs.pop_front();
            show_msg(msg);
        }
    }
}

void View::Update(Model const& model)
{
    ostream_ << "View updated with model changes" << std::endl;
}
