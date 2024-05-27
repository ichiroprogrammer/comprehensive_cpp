#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "do_heavy_algorithm.h"

// 例をシンプルに保つため、スレッド間の競合については考えない
// ref_org/main.cppを非同期にした
// 非同期インタラクションは多くのソースコード劣化の原因になる

// @@@ sample begin 0:0

int main(int, char**)
{
    auto         strings = std::vector<std::string>{};
    std::thread* thd     = nullptr;

    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            switch (buffer.at(0)) {
            case '+': {
                if (thd != nullptr) {
                    thd->join();
                    delete thd;
                }

                thd = new std::thread{[&strings, input = buffer.substr(1)] {
                    auto result = std::string{do_heavy_algorithm(input)};
                    strings.emplace_back(result);

                    for (auto i = 0U; i < strings.size(); i++) {
                        std::cout << strings[i] << std::endl;
                    }
                }};
                break;
            }
            case '.':
                // @@@ ignore begin
                // do nothing
                break;
            case '=':
                if (thd != nullptr) {
                    thd->join();
                    delete thd;
                }
                return 0;
            default:
                if (thd != nullptr) {
                    thd->join();
                    delete thd;
                }
                return 1;  // error exit
                // @@@ ignore end
            }
        }
    }

    return 0;
}
// @@@ sample end
