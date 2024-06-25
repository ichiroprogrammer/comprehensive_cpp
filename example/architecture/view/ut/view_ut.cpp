#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "model/model.h"
#include "view/view.h"

class ViewTest : public ::testing::Test {
protected:
    std::streambuf*    orig;
    std::ostringstream out;

    void SetUp() override { orig = std::cout.rdbuf(out.rdbuf()); }

    void TearDown() override { std::cout.rdbuf(orig); }
};

struct X {};
void potential_leak(int a)
{
    X* x{new X};

    if (a == 2) {  // aが2ならメモリリーク
        return;
    }

    delete x;
}
TEST_F(ViewTest, Update)
{
    View  view;
    Model model;

    view.update(model);

    ASSERT_EQ(out.str(), "View updated with model changes");

    potential_leak(2);
}
