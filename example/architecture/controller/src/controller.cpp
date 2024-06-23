#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

void Controller::setModel(Model* model) {
    this->model = model;
}

void Controller::setView(View* view) {
    this->view = view;
}
