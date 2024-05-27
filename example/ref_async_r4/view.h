#pragma once

#include <iostream>

#include "model.h"

// @@@ sample begin 0:0

class View : public Observer {
public:
    explicit View(std::ostream& os) : Observer{}, os_{os} {}

private:
    virtual void update(Model const& model) override;

    std::ostream& os_;
};
// @@@ sample end
