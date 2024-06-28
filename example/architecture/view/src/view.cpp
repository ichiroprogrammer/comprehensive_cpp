#include <iostream>

#include "logging/logger.h"
#include "view/view.h"

void View::update(Model const& model)
{
    std::cout << "View updated with model changes" << std::endl;
    LOGGER_INIT("log.txt");

    LOGGER("in update");
}
