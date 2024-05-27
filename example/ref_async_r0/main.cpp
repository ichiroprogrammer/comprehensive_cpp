#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "do_heavy_algorithm.h"
#include "scoped_guard.h"

// ref_async_org/main.cppにNull Object、RAIIを適用してリファクタリング

// @@@ sample begin 0:0

int main(int, char**)
{
    auto strings = std::vector<std::string>{};
    auto thd     = std::make_unique<std::thread>([] {});  // Null Object & RAII
    auto sg      = ScopedGuard{[&thd] { thd->join(); }};  // RAII

    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            switch (buffer[0]) {
            case '+': {
                thd->join();
                thd = std::make_unique<std::thread>([&strings, input = buffer.substr(1)] {
                    auto result = std::string{do_heavy_algorithm(input)};
                    strings.emplace_back(result);
                    for (auto const& str : strings) {  // 範囲for文
                        std::cout << str << std::endl;
                    }
                });
                break;
            }
            case '.':
                // @@@ ignore begin
                // do nothing
                break;
            case '=':
                return 0;
            default:
                return 1;  // error exit
                // @@@ ignore end
            }
        }
    }

    return 0;
}
// @@@ sample end
