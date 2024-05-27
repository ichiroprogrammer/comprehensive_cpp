#include "gtest_wrapper.h"

#include "controller.h"
#include "do_heavy_algorithm.h"
#include "model.h"
#include "ref_async_mock.h"
#include "view.h"

namespace {
// @@@ sample begin 0:0

TEST(RefAsyncR3, Model)
{
    auto view_test = ViewTest{};

    auto model = Model{};
    model.Attach(view_test);

    auto const input_model = std::vector<std::string>{"abc", "defg", "hijkl"};

    for (auto const& s : input_model) {
        model.ConvertStoreAsync(s);
    }

    view_test.WaitUpdate(input_model.size());

    ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), model.GetStrings());
}
// @@@ sample end

TEST(RefAsyncR3, Model_detach)
{
    auto view_test1 = ViewTest{};
    auto view_test2 = ViewTest{};

    auto model = Model{};
    model.Attach(view_test1);
    model.Attach(view_test2);

    model.ConvertStoreAsync("abc");

    view_test1.WaitUpdate(1);
    ASSERT_EQ(1, view_test1.GetCount());
    ASSERT_EQ(1, view_test2.GetCount());

    model.Detach(view_test2);

    model.ConvertStoreAsync("abc");

    view_test1.WaitUpdate(2);
    ASSERT_EQ(2, view_test1.GetCount());
    ASSERT_EQ(1, view_test2.GetCount());
}
}  // namespace
