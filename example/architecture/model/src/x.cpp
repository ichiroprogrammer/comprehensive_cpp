#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "model/x.h"

void X::command(std::function<void()> on_completion)
{
    fu = std::async(std::launch::async | std::launch::deferred,
                    [on_completion = std::move(on_completion)]() {
                        // 非同期処理をシミュレート
                        std::this_thread::sleep_for(std::chrono::seconds{2});
                        std::cout << "Async operation completed." << std::endl;

                        // コールバック関数を呼び出す
                        on_completion();
                    });
}

X::~X() { fu.get(); }
