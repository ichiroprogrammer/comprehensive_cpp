#include <algorithm>
#include <cassert>

#include "lib.h"

Dispatcher& Dispatcher::Inst()
{
    static Dispatcher inst;

    return inst;
}

// @@@ sample begin 0:0

void Dispatcher::Invoke(TwoPhaseTaskPtr&& task) { push_task(std::move(task), false); }

void Dispatcher::push_task(TwoPhaseTaskPtr&& task, bool stop)
{
    auto* st = task.get();
    assert(st != nullptr);
    {
        auto lock = std::lock_guard{mutex_};
        if (stoped_) {
            return;
        }
        stoped_ = stop;
        two_phase_tasks_.push(std::move(task));
    }
    st->DoPreTask();
}
// @@@ sample end

void Dispatcher::Stop()
{
    auto pre  = []() noexcept { return 0; };
    auto post = [](int&&) noexcept { return false; };

    auto task = std::make_unique<TwoPhaseTask<decltype(pre), decltype(post)>>(pre, post);

    push_task(std::move(task), true);
}

// @@@ sample begin 1:0

void Dispatcher::ExecUntilStop()
{
    for (;;) {
        auto task = TwoPhaseTaskPtr{pop_task()};

        if (!task->DoPostTask()) {
            assert(two_phase_tasks_.empty());
            stoped_ = false;
            break;
        }
    }
}

void Dispatcher::Notify(TwoPhaseTaskIF& task)
{
    auto lock = std::lock_guard{mutex_};

    task.PreTaskDone();
    pre_task_done_.notify_all();  // pop_taskでのイベント待ち解除
}

TwoPhaseTaskPtr Dispatcher::pop_task()
{
    auto lock = std::unique_lock{mutex_};

    pre_task_done_.wait(lock, [this]() noexcept {  // イベント待ち
        return !two_phase_tasks_.empty() && two_phase_tasks_.front()->IsPreTaskDone();
    });

    // キューからのTwoPhaseTaskPtrオブジェクトのポップ
    auto task = TwoPhaseTaskPtr{std::move(two_phase_tasks_.front())};
    two_phase_tasks_.pop();

    return task;
}
// @@@ sample end
