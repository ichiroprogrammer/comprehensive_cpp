#pragma once
#include <memory.h>

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

class Observer;

// @@@ sample begin 1:0

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

    Model() : worker_{&Model::worker_function, this} {}
    ~Model();

    bool ExecAsync(std::function<void()> exec);  // 非同期リクエスト
    bool IsBusy() const noexcept { return busy_; }

    void Sync();  // 非同期要求の完了待ち
    void Attach(std::unique_ptr<Observer>&& observer);

private:
    std::thread       worker_;  // 非同期処理を実現するためのワーカスレッド
    std::atomic<bool> busy_ = false;      // ExecAsyncを受け付けるか否か
    std::atomic<bool> stop_ = false;      // worker_functionの終了変数
    void              worker_function();  // スレッドのメイン関数。msg_cv_でウエイト
    void              notify();           // observer::Updateの呼び出し

    std::list<Model::msg_t> msgs_{};     // 非同期要求はmsg_tとしてリスト化される
    std::mutex              msg_mtx_{};  // リスト処理の競合の保護
    std::condition_variable msg_cv_{};   // msgs_に追加されたことの通知

    std::list<std::unique_ptr<Model::Observer>> observers_{};
};
// @@@ sample end
