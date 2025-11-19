#pragma once
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include "model/model.h"

// @@@ sample begin 1:0

class ViewCore {  // すべてのviewから保持される非同期出力オブジェクトを生成するためのシングルトン
public:
    static ViewCore& Inst()
    {
        static ViewCore inst;
        return inst;
    }

    void ShowAsync(std::string&& msg);  // 非同期出力
    void Sync();                        // 非同期出力の同期待ち

    void SetOStream(std::ostream& ostream) { ostream_ = &ostream; }  // テスト用出力切り替え

private:
    ViewCore(ViewCore const&) = delete;
    ViewCore(ViewCore&&)      = delete;
    ViewCore() : ostream_{&std::cout}, worker_{&ViewCore::worker_function, this} {}
    ~ViewCore();

    std::thread       worker_;        // 非出力を実現するためのワーカスレッド
    bool              busy_ = false;  // 非出力完了待ちに使用
    std::atomic<bool> stop_ = false;  // worker_functionの終了変数

    void show_msg(std::string const& msg)  // 非同期にmsgを出力
    {
        *ostream_ << msg;
        busy_ = false;
    }
    void worker_function();

    std::list<std::string>  msgs_{};
    std::condition_variable msg_cv_{};
    std::mutex              msg_mtx_{};

    std::ostream* ostream_;
};
// @@@ sample end

// @@@ sample begin 1:1

class View : public Model::Observer {
public:
    View() : view_core_{ViewCore::Inst()} {}
    ~View() = default;
    void ShowAsync(std::string&& msg) { view_core_.ShowAsync(std::move(msg)); }
    void Sync() { view_core_.Sync(); }
    void Update(Model const& model) override { view_core_.ShowAsync("View updated"); }

private:
    ViewCore& view_core_;  // すべての出力をViewCoreに委譲
};
// @@@ sample end
