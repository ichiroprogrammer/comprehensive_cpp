#pragma once

class Model;
class View;

class Controller {
public:
    void setModel(Model* model);
    void setView(View* view);

private:
    Model* model;
    View*  view;
};
