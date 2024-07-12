#include <iostream>

#include "logging/logger.h"
#include "view/view.h"

void View::update(Model const& model)
{
    std::cout << "View updated with model changes" << std::endl;

    LOGGER("in update");
}
