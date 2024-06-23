#pragma once
#include "model/observer.h"

class View : public Observer {
public:
    void update(Model const& model) override;
};
