#pragma once
#include <fstream>
#include <optional>
#include <utility>
#include <vector>

namespace FileUtils {

bool StoreToStream(std::ostream& os, std::vector<std::string> const& lines);
std::optional<std::vector<std::string>> Load_Strings(std::istream& is);
}  // namespace FileUtils
