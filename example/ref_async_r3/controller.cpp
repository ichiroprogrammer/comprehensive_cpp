#include <cassert>

#include "controller.h"
#include "model.h"

// @@@ sample begin 0:0

int Controller::WatchInput()
{
    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            if (auto exit_code = dispatch(buffer)) {
                return *exit_code;
            }
        }
    }

    assert(false);
    return 0;
}

std::optional<int> Controller::dispatch(std::string const& command)
{
    // @@@ ignore begin

    switch (command.at(0)) {
    case '+':
        model_.ConvertStoreAsync(command.substr(1));
        return std::nullopt;
    case '.':
        // do nothing
        return std::nullopt;
    case '=':
        return 0;
    default:
        return 1;
    }
    // @@@ ignore end
}
// @@@ sample end
