#include <future>

#include "gtest_wrapper.h"

#include "controller.h"
#include "do_heavy_algorithm.h"
#include "lib.h"
#include "model.h"
#include "ref_async_mock.h"
#include "view.h"
namespace {

// @@@ sample begin 0:0

TEST(RefAsyncR6, Model)
{
    auto view_test = ViewTest{};

    auto model = Model{};
    model.Attach(view_test);

    auto future = async(std::launch::async, [] { Dispatcher::Inst().ExecUntilStop(); });

    for (auto const s : {"abc", "defg", "hijkl"}) {
        model.ConvertStoreAsync(s);
    }

    Dispatcher::Inst().Stop();
    future.wait();

    ASSERT_EQ(3, view_test.GetCount());
    ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), model.GetStrings());
}
// @@@ sample end
}  // namespace
