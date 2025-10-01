#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "lib/nstd.h"

// @@@ sample begin 0:0

namespace Logging {
class Logger {
public:
    static Logger& Inst(char const* filename = nullptr);

    template <typename HEAD, typename... TAIL>
    void Set(char const* filename, uint32_t line_no, HEAD const& head, TAIL... tails)
    {
        auto   path     = std::string_view{filename};
        size_t npos     = path.find_last_of('/');
        auto   basename = (npos != std::string_view::npos) ? path.substr(npos + 1) : path;

        os_.width(12);
        os_ << basename << ":";

        os_.width(3);
        os_ << line_no;

        set_inner(head, tails...);
    }

    // @@@ ignore begin
    void Close();
    Logger(Logger const&)            = delete;
    Logger& operator=(Logger const&) = delete;
    // @@@ ignore end

private:
    void set_inner() { os_ << std::endl; }

    template <typename HEAD, typename... TAIL>
    void set_inner(HEAD const& head, TAIL... tails)
    {
        using Nstd::operator<<;
        os_ << ":" << head;
        set_inner(tails...);
    }

    template <typename HEAD, typename... TAIL>
    void set_inner(char sep, HEAD const& head, TAIL... tails)
    {
        using Nstd::operator<<;
        os_ << sep << head;
        set_inner(tails...);
    }

    // @@@ ignore begin
    explicit Logger(char const* filename);

    std::ofstream ofs_{};
    std::ostream& os_;

    // @@@ ignore end
};
}  // namespace Logging

#define LOGGER_INIT(filename) Logging::Logger::Inst(filename)
#define LOGGER(...) Logging::Logger::Inst().Set(__FILE__, __LINE__, __VA_ARGS__)
// @@@ sample end
