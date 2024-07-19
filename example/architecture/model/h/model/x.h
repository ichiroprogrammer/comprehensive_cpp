#pragma once

#include <chrono>
#include <functional>
#include <future>

class X {
public:
    X() = default;
    void command(std::function<void()>);

    ~X();

    std::future<void> fu;
};
