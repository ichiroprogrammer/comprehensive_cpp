#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <thread>

#include "logging/logger.h"
#include "view/view.h"

namespace {
char const* b2str(bool b) { return b ? "true" : "false"; }
}  // namespace

// @@@ sample begin 1:0

void ViewCore::ShowAsync(std::string&& msg)  // 非同期出力
{
    {
        std::unique_lock<std::mutex> lock{msg_mtx_};
        msgs_.push_back(std::move(msg));
        busy_ = true;
    }
    msg_cv_.notify_one();
}

void ViewCore::worker_function()
{
    for (;;) {
        {
            std::unique_lock<std::mutex> lock{msg_mtx_};
            msg_cv_.wait(lock, [&msgs = msgs_, &stop = stop_] { return !msgs.empty() || stop; });
            if (stop_ && msgs_.empty()) {
                return;
            }

            std::string msg = std::move(msgs_.front());

            LOGGER("Processing message", msg, ":busy", b2str(busy_));
            msgs_.pop_front();
            show_msg(msg);
        }
    }
}

void ViewCore::Sync()
{
    for (;;) {
        if (!busy_) {  // busy_のポーリング
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

ViewCore::~ViewCore()
{
    stop_ = true;
    msg_cv_.notify_one();
    worker_.join();
}
// @@@ sample end
