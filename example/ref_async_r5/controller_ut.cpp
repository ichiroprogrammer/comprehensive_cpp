#include <sstream>

#include "gtest_wrapper.h"

#include "controller.h"
#include "model.h"
#include "ref_async_mock.h"
#include "view.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR5, Controller)
{
    auto view_test   = ViewTest{};
    auto ss_view     = std::ostringstream{};
    auto view_normal = View{ss_view};
    auto model       = Model{};

    model.Attach(view_test);
    model.Attach(view_normal);

    auto ss = std::stringstream{};

    ss << "+abc" << std::endl;
    ss << "+defg" << std::endl;
    ss << "." << std::endl;
    ss << "+hijkl" << std::endl;
    ss << "=" << std::endl;

    auto controller = Controller{model, ss};

    ASSERT_EQ(0, controller.WatchInput());

    auto const exp_model = std::vector<std::string>{"ABC", "DEFG", "HIJKL"};
    view_test.WaitUpdate(exp_model.size());

    ASSERT_EQ(exp_model, model.GetStrings());

    auto ss_expect = std::ostringstream{};
    ss_expect << "ABC" << std::endl;
    ss_expect << "ABC" << std::endl << "DEFG" << std::endl;
    ss_expect << "ABC" << std::endl << "DEFG" << std::endl << "HIJKL" << std::endl;

    ASSERT_EQ(ss_expect.str(), ss_view.str());

    // エラー入力テスト
    ss << "?" << std::endl;
    ASSERT_NE(0, controller.WatchInput());
}
// @@@ sample end
}  // namespace
