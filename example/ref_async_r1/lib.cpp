#include <iostream>

#include "do_heavy_algorithm.h"
#include "lib.h"

// @@@ sample begin 0:0

namespace {
void convert_store_async(std::thread& thd, std::vector<std::string>& strings,
                         std::string const& input)
{
    thd.join();

    thd = std::thread{[&strings, input = input] {
        auto result = std::string{do_heavy_algorithm(input)};
        strings.emplace_back(result);
        for (auto const& str : strings) {
            std::cout << str << std::endl;
        }
    }};
}
}  // namespace

std::optional<int> dispatch(std::thread& thd, std::vector<std::string>& strings,
                            std::string const& command)
{
    switch (command[0]) {
    case '+':
        convert_store_async(thd, strings, command.substr(1));
        return std::nullopt;
    case '.':
        // do nothing
        return std::nullopt;
    case '=':
        return 0;
    default:
        return 1;
    }
}
// @@@ sample end
