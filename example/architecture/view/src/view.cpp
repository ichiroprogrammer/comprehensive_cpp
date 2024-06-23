#include <iostream>

#include "view/view.h"

void View::update(Model const& model)
{
    std::cout << "View updated with model changes" << std::endl;
}
