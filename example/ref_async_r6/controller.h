#pragma once
#include <future>
#include <iostream>
#include <optional>

class Model;

// @@@ sample begin 0:0

class Controller {
public:
    explicit Controller(Model& model, std::istream& is) : model_{model}, is_{is}, future_{} {}

    /// @brief 入力を受け取るスレッドを起動する
    void WatchInput();

    /// @brief 上記スレッドが終わるまで待ち合わせて、スレッドのリターンコードを返す。
    int GetExitCode();

private:
    std::optional<int> dispatch(std::string const& command);
    int                watch_input();  // WatchInputが開始するスレッドの中身

    Model&           model_;
    std::istream&    is_;
    std::future<int> future_;
};
// @@@ sample end
