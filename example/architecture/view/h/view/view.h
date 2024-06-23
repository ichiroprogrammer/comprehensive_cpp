#pragma once
#include "model/observer.h"

class View : public Observer {
public:
    void update(const Model& model) override;
};
