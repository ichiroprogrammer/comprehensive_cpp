#include <cassert>

#include "controller.h"
#include "lib.h"
#include "model.h"

// @@@ sample begin 0:0

void Controller::WatchInput()
{
    future_ = std::async(std::launch::async, [this] { return watch_input(); });
}

/// @brief Controllerのメインループ。std::istreamからコマンド文字列を受け取る。
/// @return ループ終了の原因がエラーであるならば非0。そうでなければ0。
///         この値は、GetExitCode()により取得できる。
int Controller::watch_input()
{
    for (;;) {
        auto buffer = std::string{};

        if (std::getline(is_, buffer)) {
            if (auto exit_code = dispatch(buffer)) {
                return *exit_code;
            }
        }
    }

    assert(false);
    return 0;
}

/// @brief 受け取った文字列をパースして、ディスパッチする
/// @param std::istreamから受け取った文字列
/// @return プログラムを終了する場合、exitコードを返す
std::optional<int> Controller::dispatch(std::string const& command)
{
    switch (command.at(0)) {
    case '+':
        model_.ConvertStoreAsync(command.substr(1));
        return std::nullopt;
    case '.':
        // do nothing
        return std::nullopt;
    case '=':
        Dispatcher::Inst().Stop();  // プログラム終了処理
        return 0;
    // @@@ ignore begin
    default:
        Dispatcher::Inst().Stop();
        return 1;
        // @@@ ignore end
    }
}

int Controller::GetExitCode() { return future_.get(); }
// @@@ sample end
