#include <sstream>

#include "gtest_wrapper.h"

#include "controller.h"
#include "model.h"
#include "ref_async_mock.h"
#include "view.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR5, Model)
{
    auto view_test   = ViewTest{};
    auto ss_view     = std::ostringstream{};
    auto view_normal = View{ss_view};
    auto model       = Model{};

    model.Attach(view_normal);
    model.Attach(view_test);

    auto const input_model = std::vector<std::string>{"abc", "defg", "hijkl"};

    for (auto const& s : input_model) {
        model.ConvertStoreAsync(s);
    }

    view_test.WaitUpdate(input_model.size());

    ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), model.GetStrings());

    auto ss_expect = std::ostringstream{};  // viewのテスト
    ss_expect << "ABC" << std::endl;
    ss_expect << "ABC" << std::endl << "DEFG" << std::endl;
    ss_expect << "ABC" << std::endl << "DEFG" << std::endl << "HIJKL" << std::endl;

    ASSERT_EQ(ss_expect.str(), ss_view.str());
}
// @@@ sample end
}  // namespace
