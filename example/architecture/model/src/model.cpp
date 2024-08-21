#include <atomic>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <iostream>
// @@@ sample begin 0:0

#include <iterator>  // stdの使用

#include "./x.h"             // ローカルヘッダの使用
#include "logging/logger.h"  // logger.aの使用
#include "model/model.h"     // model.aの使用
// @@@ sample end

Model::~Model()
{
    stop_ = true;
    busy_ = false;
    msg_cv_.notify_one();
    worker_.join();
}

void Model::Sync()
{
    for (;;) {
        if (!busy_) {  // busy_のポーリング
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// @@@ sample begin 1:1

bool Model::ExecAsync(std::function<void()> exec)  // Modelに対する非同期要求
{
    // 非同期要求のキューイングはしないが、キューイング可能に変更は容易
    if (busy_) {
        return false;
    }

    {
        std::unique_lock<std::mutex> lock{msg_mtx_};
        msgs_.emplace_back(std::move(exec));
        busy_ = true;
    }
    msg_cv_.notify_one();

    return true;
}
// @@@ sample end
// @@@ sample begin 1:2

void Model::worker_function()  // スレッドのメイン関数
{
    for (;;) {
        msg_t msg;
        {
            std::unique_lock<std::mutex> lock{msg_mtx_};
            msg_cv_.wait(lock, [&msgs = msgs_, &stop = stop_] { return !msgs.empty() || stop; });
            if (stop_ && msgs_.empty()) {
                return;
            }

            msg = std::move(msgs_.front());
            msgs_.pop_front();
        }

        msg.exec();  // ExecAsync(exec)で渡された関数オブジェクトの非同期呼び出し
        busy_ = false;

        notify();  // オブザーバーへの通知処理
    }
}
// @@@ sample end
// @@@ sample begin 1:3

void Model::Attach(std::unique_ptr<Observer>&& observer)  // オブザーバーのアタッチ
{
    observers_.emplace_back(std::move(observer));
}

void Model::notify()
{
    for (auto const& observer : observers_) {
        observer->Update(*this);
    }
}
// @@@ sample end
