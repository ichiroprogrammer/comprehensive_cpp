#include <algorithm>
#include <numeric>
#include <sstream>

#include "gtest_wrapper.h"

#include "controller.h"
#include "do_heavy_algorithm.h"
#include "lib.h"
#include "model.h"
#include "ref_async_mock.h"
#include "view.h"

namespace {

// @@@ sample begin 0:0

std::string gen_expect(std::vector<std::string> const& strs)
{
    auto cr = std::vector<std::string>{strs.size()};
    std::transform(strs.begin(), strs.end(), cr.begin(),
                   [](std::string const& s) { return s + '\n'; });

    auto pattern = std::vector<std::string>{};
    std::partial_sum(cr.begin(), cr.end(), std::back_inserter(pattern));

    return std::accumulate(pattern.begin(), pattern.end(), std::string{});
}

TEST(RefAsyncR6, Controller)
{
    auto view_test   = ViewTest{};
    auto ss_view     = std::ostringstream{};
    auto view_normal = View{ss_view};
    auto model       = Model{};

    model.Attach(view_test);
    model.Attach(view_normal);

    auto ss = std::stringstream{};

    ss << "+abc" << std::endl;
    ss << "." << std::endl;
    ss << "+defg" << std::endl;
    ss << "." << std::endl;
    ss << "+hijkl" << std::endl;
    ss << "." << std::endl;
    ss << "=" << std::endl;

    auto controller = Controller{model, ss};

    controller.WatchInput();
    Dispatcher::Inst().ExecUntilStop();
    ASSERT_EQ(0, controller.GetExitCode());

    auto const exp_model = std::vector<std::string>{"ABC", "DEFG", "HIJKL"};
    view_test.WaitUpdate(exp_model.size());

    ASSERT_EQ(exp_model, model.GetStrings());

    ASSERT_EQ(gen_expect(exp_model), ss_view.str());
}

TEST(RefAsyncR6, Controller2)
{
    auto view_test   = ViewTest{};
    auto ss_view     = std::ostringstream{};
    auto view_normal = View{ss_view};
    auto model       = Model{};

    model.Attach(view_test);
    model.Attach(view_normal);

    auto ss = std::stringstream{};

    ss << "+abc" << std::endl;
    ss << "+def" << std::endl;
    ss << "+ghi" << std::endl;
    ss << "=" << std::endl;

    auto controller = Controller{model, ss};

    controller.WatchInput();
    Dispatcher::Inst().ExecUntilStop();
    ASSERT_EQ(0, controller.GetExitCode());

    view_test.WaitUpdate(3);

    ASSERT_EQ(gen_expect({"ABC", "DEF", "GHI"}), ss_view.str());
}
// @@@ sample end
}  // namespace
