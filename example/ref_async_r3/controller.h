#pragma once
#include <iostream>
#include <optional>

class Model;

// @@@ sample begin 0:0

class Controller {
public:
    explicit Controller(Model& model) : model_{model} {}

    int WatchInput();

private:
    std::optional<int> dispatch(std::string const& command);

    Model& model_;
};
// @@@ sample end
