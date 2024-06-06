#include <cassert>
#include <iostream>
#include <optional>
#include <regex>

#include "file_utils/load_store.h"
#include "file_utils/load_store_row.h"

namespace FileUtils {

bool StoreToStream(std::ostream& os, std::vector<std::string> const& lines)
{
    for (auto const& line : lines) {
        os << line;
    }

    return true;
}

std::optional<std::vector<std::string>> Load_Strings(std::istream& is)
{
    auto content = std::vector<std::string>{};
    auto line    = std::string{};

    while (std::getline(is, line)) {
        auto ss = std::ostringstream{};

        ss << line << std::endl;
        content.emplace_back(ss.str());
    }

    return content;
}
}  // namespace FileUtils
