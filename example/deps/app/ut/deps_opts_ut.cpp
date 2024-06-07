#include "gtest_wrapper.h"

#include "deps_opts.h"
#include "lib/nstd.h"

namespace App {
namespace {

TEST(deps_args, DepsOpts)
{
    using FileUtils::Paths_t;

    char prog[]          = "prog";
    char cmd_p[]         = "p";
    char cmd_s[]         = "s";
    char cmd_p2s[]       = "p2s";
    char cmd_p2p[]       = "p2p";
    char cmd_a[]         = "a";
    char cmd_a2pu[]      = "a2pu";
    char cmd_help[]      = "help";
    char cmd_dd_help[]   = "--help";
    char cmd_h[]         = "h";
    char cmd_d_h[]       = "-h";
    char cmd_unknown[]   = "unknown";
    char opt_in[]        = "--in";
    char opt_in_arg[]    = "in-file";
    char opt_out[]       = "--out";
    char opt_out_arg[]   = "out-file";
    char opt_e[]         = "-e";
    char opt_exclude[]   = "--exclude";
    char opt_e_arg[]     = "pattern.*";
    char opt_recursive[] = "--recursive";
    char opt_src_pkg[]   = "--src_as_pkg";
    char opt_log[]       = "--log";
    char opt_log_arg[]   = "log-file";
    char opt_log_dash[]  = "-";
    char opt_R[]         = "-R";
    char opt_s[]         = "-s";
    char opt_help[]      = "--help";
    char opt_h[]         = "-h";
    char dir0[]          = "dir0";
    char dir1[]          = "dir1";
    char dir2[]          = "dir2";

    {
        char* const argv[]{prog, cmd_p, opt_recursive, opt_out, opt_out_arg, dir0, dir1, dir2};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg, d_opt.GetCmd());
        ASSERT_EQ("", d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_TRUE(d_opt.IsRecursive());
        ASSERT_EQ((Paths_t{dir0, dir1, dir2}), d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[] = {prog, cmd_p, opt_src_pkg, opt_out, opt_out_arg, dir0, dir1, dir2};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg, d_opt.GetCmd());
        ASSERT_EQ("", d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_TRUE(d_opt.IsSrcPkg());
        ASSERT_EQ((Paths_t{dir0, dir1, dir2}), d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_s, opt_src_pkg, opt_out, opt_out_arg, dir0, dir1, dir2};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenSrc, d_opt.GetCmd());
        ASSERT_EQ("", d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_TRUE(d_opt.IsSrcPkg());
        ASSERT_EQ((Paths_t{dir0, dir1, dir2}), d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_p2s, opt_R, opt_in, opt_in_arg, opt_exclude, opt_e_arg, dir0};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg2Srcs, d_opt.GetCmd());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_EQ("", d_opt.Out());
        ASSERT_TRUE(d_opt.IsRecursive());
        ASSERT_EQ((Paths_t{dir0}), d_opt.Dirs());
        ASSERT_TRUE(d_opt);
        ASSERT_EQ(opt_e_arg, d_opt.Exclude());
    }
    {
        char* const argv[]{prog, cmd_p2s, opt_s, opt_in, opt_in_arg, opt_e, opt_e_arg, dir0};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg2Srcs, d_opt.GetCmd());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_EQ("", d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_TRUE(d_opt.IsSrcPkg());
        ASSERT_EQ((Paths_t{dir0}), d_opt.Dirs());
        ASSERT_TRUE(d_opt);
        ASSERT_EQ(opt_e_arg, d_opt.Exclude());
    }
    {
        char* const argv[]{prog, cmd_p2p, opt_in, opt_in_arg, opt_out, opt_out_arg};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg2Pkg, d_opt.GetCmd());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_EQ(Paths_t{}, d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_a, opt_in, opt_in_arg, opt_out, opt_out_arg};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenArch, d_opt.GetCmd());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_EQ(Paths_t{}, d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_a2pu, opt_in, opt_in_arg, opt_out, opt_out_arg};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPlantUml, d_opt.GetCmd());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_FALSE(d_opt.IsRecursive());
        ASSERT_EQ(Paths_t{}, d_opt.Dirs());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_help};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_dd_help};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_h};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_d_h};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_unknown};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::NotCmd, d_opt.GetCmd());
        ASSERT_FALSE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_p, opt_recursive, opt_out, opt_out_arg, opt_help};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_p, opt_recursive, opt_out, opt_out_arg, opt_h};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::Help, d_opt.GetCmd());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_p, opt_log, opt_log_arg, opt_out, opt_out_arg};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg, d_opt.GetCmd());
        ASSERT_EQ(opt_log_arg, d_opt.Log());
        ASSERT_EQ(opt_out_arg, d_opt.Out());
        ASSERT_TRUE(d_opt);
    }
    {
        char* const argv[]{prog, cmd_p, opt_log, opt_log_dash, opt_in, opt_in_arg};

        auto d_opt = DepsOpts{Nstd::ArrayLength(argv), argv};

        ASSERT_EQ(DepsOpts::Cmd::GenPkg, d_opt.GetCmd());
        ASSERT_EQ(opt_log_dash, d_opt.Log());
        ASSERT_EQ(opt_in_arg, d_opt.In());
        ASSERT_TRUE(d_opt);
    }
}
}  // namespace
}  // namespace App
