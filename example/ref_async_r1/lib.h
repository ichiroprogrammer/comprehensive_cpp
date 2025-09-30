#pragma once
#include <optional>
#include <string>
#include <thread>
#include <vector>

extern std::optional<int> dispatch(std::thread& thd, std::vector<std::string>& strings, std::string const& command);
