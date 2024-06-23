#include "view/view.h"
#include <iostream>

void View::update(const Model& model) {
    std::cout << "View updated with model changes" << std::endl;
}
