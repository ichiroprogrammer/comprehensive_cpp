#pragma once

#include <chrono>
#include <functional>
#include <future>

class SlowMover {
public:
    SlowMover() = default;
    void command(std::function<void()>);

    ~SlowMover();

    std::future<void> fu;
};
