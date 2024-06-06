#pragma once
#include <fstream>
#include <optional>
#include <string>

namespace FileUtils {

template <typename T>
bool StoreToFile(std::string_view filename, T const& t, bool (*ss)(std::ostream& os, T const&))
{
    auto fout = std::ofstream{filename.data()};

    if (!fout) {
        return false;
    }

    return (*ss)(fout, t);
}

template <typename T>
std::optional<T> LoadFromFile(std::string_view filename, std::optional<T> (*ls)(std::istream& os))
{
    auto fin = std::ifstream{filename.data()};

    if (!fin) {
        return std::nullopt;
    }

    return (*ls)(fin);
}
}  // namespace FileUtils
