#include <getopt.h>

#include <cassert>
#include <sstream>

#include "deps_opts.h"
#include "lib/nstd.h"

namespace App {
std::string DepsOpts::Help()
{
    auto ss = std::ostringstream{};

    ss << "deps CMD [option] [DIRS] ..." << std::endl;
    ss << "   CMD:" << std::endl;
    ss << "         p    : generate package to OUT." << std::endl;
    ss << "         s    : generate srcs with incs to OUT." << std::endl;
    ss << "         p2s  : generate package and srcs pairs to OUT." << std::endl;
    ss << "         p2p  : generate packages' dependencies to OUT." << std::endl;
    ss << "         a    : generate structure to OUT from p2p output." << std::endl;
    ss << "         a2pu : generate plant uml package to OUT from p2p output." << std::endl;
    ss << "         cyc  : exit !0 if found cyclic dependencies." << std::endl;
    ss << "         help : show help message." << std::endl;
    ss << "         h    : same as help(-h, --help)." << std::endl;
    ss << std::endl;
    ss << "   options:" << std::endl;
    ss << "         --in IN     : use IN to execute CMD." << std::endl;
    ss << "         --out OUT   : CMD outputs to OUT." << std::endl;
    ss << "         --recursive : search dir as package from DIRS or IN contents." << std::endl;
    ss << "         -R          : same as --recursive." << std::endl;
    ss << "         --src_as_pkg: every src is as a package." << std::endl;
    ss << "         -s          : same as --src_as_pkg." << std::endl;
    ss << "         --log LOG   : logging to LOG(if LOG is \"-\", using STDOUT)." << std::endl;
    ss << "         --exclude PTN : exclude dirs which matchs to PTN(JS regex)." << std::endl;
    ss << "         -e PTN      : same as --exclude." << std::endl;
    ss << std::endl;
    ss << "   DIRS: use DIRS to execute CMD." << std::endl;
    ss << "   IN  : 1st line in this file must be" << std::endl;
    ss << "             #dir2srcs for pkg-srcs file" << std::endl;
    ss << "         or" << std::endl;
    ss << "             #dir for pkg file." << std::endl << std::endl;

    return ss.str();
}

DepsOpts::Cmd DepsOpts::parse_command(int argc, char* const* argv)
{
    if (argc < 2) {
        return Cmd::NotCmd;
    }

    auto command = std::string{argv[1]};

    if (command == "p") {
        return Cmd::GenPkg;
    }
    if (command == "s") {
        return Cmd::GenSrc;
    }
    else if (command == "p2s") {
        return Cmd::GenPkg2Srcs;
    }
    else if (command == "p2p") {
        return Cmd::GenPkg2Pkg;
    }
    else if (command == "a") {
        return Cmd::GenArch;
    }
    else if (command == "a2pu") {
        return Cmd::GenPlantUml;
    }
    else if (command == "cyc") {
        return Cmd::GenCyclic;
    }
    else if (command == "h" || command == "help" || command == "-h" || command == "--help") {
        return Cmd::Help;
    }

    return Cmd::NotCmd;
}

bool DepsOpts::parse_opt(int opt_char, DepsOpts::DepsOptsData& data) noexcept
{
    switch (opt_char) {
    case 'i':
        data.in = optarg;
        return true;
    case 'e':
        data.exclude = optarg;
        return true;
    case 'o':
        data.out = optarg;
        return true;
    case 'l':
        data.log = optarg;
        return true;
    case 'R':
        data.recursive = true;
        return true;
    case 's':
        data.src_as_pkg = true;
        return true;
    case 'h':
        data.cmd = Cmd::Help;
        return false;
    default:
        return false;
    }
}

DepsOpts::DepsOptsData DepsOpts::parse(int argc, char* const* argv)
{
    DepsOptsData data{parse_command(argc, argv)};

    if (data.cmd == Cmd::NotCmd || data.cmd == Cmd::Help) {
        return data;
    }

    optind = 2;
    static struct option const opts[]
        = {{"in", required_argument, 0, 'i'},      {"out", required_argument, 0, 'o'},
           {"exclude", required_argument, 0, 'e'}, {"recursive", no_argument, 0, 'R'},
           {"src_as_pkg", no_argument, 0, 's'},    {"log", required_argument, 0, 'l'},
           {"help", no_argument, 0, 'h'},          {0, 0, 0, 0}};

    for (;;) {
        auto opt_char = getopt_long(argc, argv, "i:o:e:l:Rsh", opts, nullptr);

        if (!parse_opt(opt_char, data)) {
            break;
        }
    }

    if (optind < argc) {
        while (optind < argc) {
            data.dirs.emplace_back(FileUtils::NormalizeLexically(argv[optind++]));
        }
    }

    return data;
}

namespace {
std::string to_string_cmd(DepsOpts::Cmd cmd)
{
    switch (cmd) {
    case DepsOpts::Cmd::GenPkg:
        return "GenPkg";
    case DepsOpts::Cmd::GenSrc:
        return "GenSrc";
    case DepsOpts::Cmd::GenPkg2Srcs:
        return "GenPkg2Srcs";
    case DepsOpts::Cmd::GenPkg2Pkg:
        return "GenPkg2Pkg";
    case DepsOpts::Cmd::GenPlantUml:
        return "GenPlantUml";
    case DepsOpts::Cmd::GenCyclic:
        return "GenCyclic";
    case DepsOpts::Cmd::Help:
        return "Help";
    case DepsOpts::Cmd::NotCmd:
    default:
        return "NotCmd";
    }
}
}  // namespace

std::string ToStringDepsOpts(DepsOpts const& deps_opts, std::string_view indent)
{
    auto       ss      = std::ostringstream{};
    char const cmd[]   = "cmd       : ";
    auto const indent2 = std::string(Nstd::ArrayLength(cmd) - 1, ' ') + std::string{indent};

    ss << std::boolalpha;

    ss << indent << cmd << to_string_cmd(deps_opts.GetCmd()) << std::endl;
    ss << indent << "in        : " << deps_opts.In() << std::endl;
    ss << indent << "out       : " << deps_opts.Out() << std::endl;
    ss << indent << "recursive : " << deps_opts.IsRecursive() << std::endl;
    ss << indent << "src_as_pkg: " << deps_opts.IsSrcPkg() << std::endl;
    ss << indent << "log       : " << deps_opts.Log() << std::endl;
    ss << indent << "dirs      : " << FileUtils::ToStringPaths(deps_opts.Dirs(), "\n" + indent2)
       << std::endl;
    ss << indent << "exclude   : " << deps_opts.Exclude() << std::endl;
    ss << indent << "parsed    : " << !!deps_opts;

    return ss.str();
}
}  // namespace App
