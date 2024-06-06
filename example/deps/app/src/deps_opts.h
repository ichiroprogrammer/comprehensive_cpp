#pragma once
#include <ostream>

#include "file_utils/path_utils.h"

namespace App {
class DepsOpts {
public:
    enum class Cmd {
        GenPkg,
        GenSrc,
        GenPkg2Srcs,
        GenPkg2Pkg,
        GenArch,
        GenPlantUml,
        GenCyclic,
        Help,
        NotCmd,
    };
    explicit DepsOpts(int argc, char* const* argv) : data_{parse(argc, argv)} {}
    static std::string Help();

    Cmd                       GetCmd() const noexcept { return data_.cmd; }
    std::string const&        In() const noexcept { return data_.in; }
    std::string const&        Out() const noexcept { return data_.out; }
    std::string const&        Log() const noexcept { return data_.log; }
    bool                      IsRecursive() const noexcept { return data_.recursive; }
    bool                      IsSrcPkg() const noexcept { return data_.src_as_pkg; }
    FileUtils::Paths_t const& Dirs() const noexcept { return data_.dirs; }
    std::string const&        Exclude() const noexcept { return data_.exclude; }

    explicit operator bool() const { return data_.cmd != Cmd::NotCmd; }

private:
    struct DepsOptsData {
        DepsOptsData(Cmd cmd_arg) noexcept : cmd{cmd_arg} {}
        Cmd                cmd;
        std::string        in{};
        std::string        out{};
        std::string        log{};
        FileUtils::Paths_t dirs{};
        std::string        exclude{};
        bool               recursive{false};
        bool               src_as_pkg{false};
    };
    DepsOptsData const data_;

    static DepsOptsData parse(int argc, char* const* argv);
    static Cmd          parse_command(int argc, char* const* argv);
    static bool         parse_opt(int opt_char, DepsOptsData& data) noexcept;
};

// @@@ sample begin 0:0

std::string          ToStringDepsOpts(DepsOpts const& deps_opts, std::string_view indent = "");
inline std::ostream& operator<<(std::ostream& os, DepsOpts const& opts)
{
    return os << ToStringDepsOpts(opts);
}
// @@@ sample end
}  // namespace App
