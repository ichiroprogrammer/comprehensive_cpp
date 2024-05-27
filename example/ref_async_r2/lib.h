#pragma once

#include <optional>
#include <string>
#include <thread>
#include <vector>

// @@@ sample begin 0:0

class Model {
public:
    Model() : thd_{[] {}}, strings_{} {}
    ~Model() { thd_.join(); }
    void ConvertStoreAsync(std::string const& input);

private:
    std::thread              thd_;
    std::vector<std::string> strings_;
};
// @@@ sample end

extern std::optional<int> dispatch(Model& model, std::string const& command);
