#include <cassert>
#include <iostream>
#include <memory>

#include "do_heavy_algorithm.h"
#include "lib.h"
#include "scoped_guard.h"

// @@@ sample begin 0:0

namespace {
int main_loop()
{
    auto strings = std::vector<std::string>{};
    auto thd     = std::thread{[] {}};                         // NullObject & RAII
    auto sg      = Nstd::ScopedGuard{[&thd] { thd.join(); }};  // RAII

    for (;;) {
        auto buffer = std::string{};

        if (std::getline(std::cin, buffer)) {
            if (auto exit_code = dispatch(thd, strings, buffer)) {
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
