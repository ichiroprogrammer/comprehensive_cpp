#pragma once

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>

class TwoPhaseTaskIF;

// @@@ sample begin 0:0

/// @typedef TwoPhaseTaskPtr
/// @brief std::unique_ptr<TwoPhaseTaskIF>オブジェクトを便利に使うためのエイリアス。
using TwoPhaseTaskPtr = std::unique_ptr<TwoPhaseTaskIF>;
// @@@ sample end

// @@@ sample begin 1:0

/// @brief Dispatcherに代理実行するためのタスクを定義するためのクラスのインターフェース。
///        TwoPhaseTask<>のベースクラス。
class TwoPhaseTaskIF {
public:
    TwoPhaseTaskIF() = default;

    void DoPreTask() { do_pre_task(); }
    bool IsPreTaskDone() const { return is_pre_task_done_; }
    void PreTaskDone() { is_pre_task_done_ = true; }
    bool DoPostTask() { return do_post_task(); }
    virtual ~TwoPhaseTaskIF() = default;

    // @@@ ignore begin
    TwoPhaseTaskIF(TwoPhaseTaskIF const&)                = delete;
    TwoPhaseTaskIF& operator=(TwoPhaseTaskIF const&)     = delete;
    TwoPhaseTaskIF(TwoPhaseTaskIF&&) noexcept            = delete;
    TwoPhaseTaskIF& operator=(TwoPhaseTaskIF&&) noexcept = delete;
    // @@@ ignore end

private:
    bool is_pre_task_done_{false};

    virtual void do_pre_task()  = 0;
    virtual bool do_post_task() = 0;
};
// @@@ sample end

// @@@ sample begin 2:0

/// @brief InvokeされたTwoPhaseTaskPtrの
///         * PreTaskを非同期に呼び出し、終了時自分に通知する。
///         * PreTask終了通知をトリガーに、PreTaskの結果を引数にしてPostTaskを
///           ExecUntilStop()のコンテキスト上で呼び出す。
///        ExecUntilStop()は、Stop()が呼び出されるまでリターンしない。
class Dispatcher {
public:
    static Dispatcher& Inst();

    /// @brief TwoPhaseTaskPtrを登録してPreTaskを非同期実行。
    /// @param TwoPhaseTaskPtrオブジェクトのrvalue。
    void Invoke(TwoPhaseTaskPtr&&);

    /// @brief 登録されているTaskの処理が終わったら、ExecUntilStop()がリターンする。
    void Stop();

    /// @brief PreTaskがその終了を通知する
    void Notify(TwoPhaseTaskIF& task);

    /// @brief 終了したPreTaskの対のPostTaskをPreTaskの戻り値を添えて呼び出す。
    void ExecUntilStop();

    // @@@ ignore begin
    Dispatcher(Dispatcher const&)                = delete;
    Dispatcher& operator=(Dispatcher const&)     = delete;
    Dispatcher(Dispatcher&&) noexcept            = delete;
    Dispatcher& operator=(Dispatcher&&) noexcept = delete;
    // @@@ ignore end

private:
    Dispatcher() = default;
    TwoPhaseTaskPtr pop_task();
    void            push_task(TwoPhaseTaskPtr&& task, bool stop);

    std::mutex mutex_{};

    std::queue<TwoPhaseTaskPtr> two_phase_tasks_{};
    std::condition_variable     pre_task_done_{};
    bool                        stoped_{false};
};
// @@@ sample end

// @@@ sample begin 3:0

/// @brief Dispatcherが管理するタスクを管理するTwoPhaseTaskIFの具象クラス
/// @tparam PRE  非同期に行われる処理を記述したラムダ式の型。重い処理を行う。
/// @tparam POST PREの実行の結果をModelに保存するラムダ式の型。
///               この処理は、スレッドセーフでないため、単一のスレッドで行う。
///               ブロックしたり、重い処理を行ってはならない。
template <typename PRE, typename POST>
class TwoPhaseTask final : public TwoPhaseTaskIF {
public:
    using Result = decltype(std::declval<PRE>()());  // PRE()の戻り値型

    // POSTは、bool post(T)のような関数型でなければならない。
    static_assert(std::is_same_v<bool, decltype(std::declval<POST>()(Result()))>);

    TwoPhaseTask(PRE pre_task, POST post_task) : pre_task_{pre_task}, post_task_{post_task}, result_{} {}

    virtual ~TwoPhaseTask() override = default;

private:
    /// @brief PREを非同期実行し、終了をDispatcherに通知
    virtual void do_pre_task() override
    {
        result_ = std::async(std::launch::async, [this] {
            auto ret = Result{pre_task_()};
            Dispatcher::Inst().Notify(*this);
            return ret;
        });
    }

    /// @brief PREの戻り値を添えてPOSTを同期実行
    virtual bool do_post_task() override { return post_task_(result_.get()); }

    PRE                 pre_task_;
    POST                post_task_;
    std::future<Result> result_;
};
// @@@ sample end

// @@@ sample begin 4:0

/// @brief TwoPhaseTaskIFオブジェクトを生成するファクトリ関数
/// @tparam PRE       TwoPhaseTaskのPRE
/// @tparam POST_BODY TwoPhaseTaskのPOSTの中身で、戻り値はvoid
template <typename PRE, typename POST_BODY>
TwoPhaseTaskPtr MakeTwoPhaseTaskPtr(PRE pre_task, POST_BODY post_body)
{
    using T        = decltype(std::declval<PRE>()());
    auto post_task = [post_body](T&& pre_result) {
        post_body(std::move(pre_result));
        return true;
    };

    return std::make_unique<TwoPhaseTask<PRE, decltype(post_task)>>(pre_task, post_task);
}
// @@@ sample end
