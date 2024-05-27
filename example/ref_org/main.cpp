#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "do_heavy_algorithm.h"

// @@@ sample begin 0:0

int main(int, char**)
{
    auto strings = std::vector<std::string>{};

    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            switch (buffer.at(0)) {
            case '+': {
                auto result = std::string{do_heavy_algorithm(buffer.substr(1))};
                strings.emplace_back(result);
                for (auto i = 0U; i < strings.size(); i++) {
                    std::cout << strings[i] << std::endl;
                }
                break;
            }
            case '.':
                // do nothing
                break;
            case '=':
                return 0;
            default:
                return 1;  // error exit
            }
        }
    }

    return 0;
}
// @@@ sample end
