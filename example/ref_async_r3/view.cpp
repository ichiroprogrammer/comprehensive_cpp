#include "view.h"

// @@@ sample begin 0:0

void View::update(Model const& model)
{
    for (auto const& str : model.GetStrings()) {
        std::cout << str << std::endl;
    }
}
// @@@ sample end
