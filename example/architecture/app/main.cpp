#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main()
{
    Controller controller;
    Model      model;
    View       view{std::cout};

    controller.setModel(&model);
    controller.setView(&view);

    return 0;
}
