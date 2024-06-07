#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "dependency/deps_scenario.h"
#include "deps_opts.h"
#include "logging/logger.h"

namespace {

class OStreamSelector {
public:
    explicit OStreamSelector(std::string const& out) : os_{select(out, out_f_)} {}
    std::ostream& OStream() noexcept { return os_; }

private:
    std::ofstream out_f_{};
    std::ostream& os_;

    static std::ostream& select(std::string const& out, std::ofstream& out_f)
    {
        if (out.size()) {
            out_f.open(out);
            assert(out_f);
            return out_f;
        }
        else {
            return std::cout;
        }
    }
};

class ScenarioGeneratorNop : public Dependency::ScenarioGenerator {
public:
    explicit ScenarioGeneratorNop(bool no_error) : no_error_{no_error} {}
    virtual bool Output(std::ostream&) const noexcept override { return no_error_; }

private:
    bool no_error_;
};

// @@@ sample begin 0:0
std::unique_ptr<Dependency::ScenarioGenerator> gen_scenario(App::DepsOpts const& opt)
try {
    using namespace Dependency;

    switch (opt.GetCmd()) {
    case App::DepsOpts::Cmd::GenPkg:
        LOGGER("start GenPkg");
        return std::make_unique<PkgGenerator>(opt.In(), opt.IsRecursive(), opt.Dirs(),
                                              opt.Exclude());
    case App::DepsOpts::Cmd::GenSrc:
        LOGGER("start GenPkg");
        return std::make_unique<SrcsGenerator>(opt.In(), opt.IsRecursive(), opt.Dirs(),
                                               opt.Exclude());
    // @@@ ignore begin
    case App::DepsOpts::Cmd::GenPkg2Srcs:
        LOGGER("start GenPkg2Srcs");
        return std::make_unique<Pkg2SrcsGenerator>(opt.In(), opt.IsRecursive(), opt.IsSrcPkg(),
                                                   opt.Dirs(), opt.Exclude());
    case App::DepsOpts::Cmd::GenPkg2Pkg:
        LOGGER("start GenPkg2Pkg");
        return std::make_unique<Pkg2PkgGenerator>(opt.In(), opt.IsRecursive(), opt.IsSrcPkg(),
                                                  opt.Dirs(), opt.Exclude());
    case App::DepsOpts::Cmd::GenArch:
        LOGGER("start GenArch");
        return std::make_unique<ArchGenerator>(opt.In());
    case App::DepsOpts::Cmd::GenPlantUml:
        LOGGER("start GenPlantUml");
        return std::make_unique<Arch2PUmlGenerator>(opt.In());
    case App::DepsOpts::Cmd::GenCyclic:
        LOGGER("start GenCyclic");
        return std::make_unique<CyclicGenerator>(opt.In());
    case App::DepsOpts::Cmd::Help:
        std::cout << App::DepsOpts::Help() << std::endl;
        return std::make_unique<ScenarioGeneratorNop>(true);
    case App::DepsOpts::Cmd::NotCmd:
    default:
        std::cout << App::DepsOpts::Help() << std::endl;
        return std::make_unique<ScenarioGeneratorNop>(false);
        // @@@ ignore end
    }
}
catch (std::runtime_error const& e) {
    LOGGER("error occured:", e.what());

    std::cerr << e.what() << std::endl;

    return std::make_unique<ScenarioGeneratorNop>(false);
}

// @@@ ignore begin
catch (...) {
    LOGGER("unknown error occured:");

    return std::make_unique<ScenarioGeneratorNop>(false);
}
}  // namespace
// @@@ ignore end

int main(int argc, char* argv[])
{
    App::DepsOpts d_opt{argc, argv};

    LOGGER_INIT(d_opt.Log() == "-" ? nullptr : d_opt.Log().c_str());

    LOGGER("Options", '\n', d_opt);

    auto out_sel   = OStreamSelector{d_opt.Out()};
    auto exit_code = gen_scenario(d_opt)->Output(out_sel.OStream()) ? 0 : -1;

    LOGGER("Exit", exit_code);

    return exit_code;
}
// @@@ sample end
