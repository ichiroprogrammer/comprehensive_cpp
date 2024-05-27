#pragma once
#include <iostream>
#include <optional>

class Model;

// @@@ sample begin 0:0

class Controller {
public:
    explicit Controller(Model& model, std::istream& is) : model_{model}, is_{is} {}

    int WatchInput();

private:
    std::optional<int> dispatch(std::string const& command);

    Model&        model_;
    std::istream& is_;
};
// @@@ sample end
