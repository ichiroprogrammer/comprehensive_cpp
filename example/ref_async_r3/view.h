#pragma once

#include <iostream>

#include "model.h"

// @@@ sample begin 0:0

class View : public Observer {
private:
    virtual void update(Model const& model) override;
};
// @@@ sample end
