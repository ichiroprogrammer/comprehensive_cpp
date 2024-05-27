#include <iostream>

#include "do_heavy_algorithm.h"
#include "lib.h"

// @@@ sample begin 0:0

void Model::ConvertStoreAsync(std::string const& input)
{
    thd_.join();

    thd_ = std::thread{[&sv = strings_, input = input] {
        sv.emplace_back(do_heavy_algorithm(input));

        for (auto const& str : sv) {
            std::cout << str << std::endl;
        }
    }};
}

std::optional<int> dispatch(Model& model, std::string const& command)
{
    // @@@ ignore begin

    switch (command.at(0)) {
    case '+':
        model.ConvertStoreAsync(command.substr(1));
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
