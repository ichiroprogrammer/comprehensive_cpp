#pragma once

#include <atomic>

#include "do_heavy_algorithm.h"

class Model;
class Oberver;

// @@@ sample begin 0:0

class ViewTest : public Observer {
public:
    void WaitUpdate(uint32_t num) noexcept  // num回、updateが呼び出されるまでブロック
    {
        while (update_counter_ != num) {  // ポーリングは避けるべきだが、単体テストなら問題ない
            org_msec_sleep(100);
        }
    }

    uint32_t GetCount() const noexcept { return update_counter_; }

private:
    virtual void update(Model const&) noexcept override { ++update_counter_; }

    std::atomic<uint32_t> update_counter_{0};
};
// @@@ sample end
