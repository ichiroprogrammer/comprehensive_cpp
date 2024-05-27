#include <cassert>
#include <iostream>

#include "lib.h"

// @@@ sample begin 0:0

namespace {
int main_loop()
{
    auto model = Model{};

    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            if (auto exit_code = dispatch(model, buffer)) {
                return *exit_code;
            }
        }
    }

    assert(false);
    return 0;
}
}  // namespace

int main(int, char**) { return main_loop(); }
// @@@ sample end
