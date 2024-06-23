#include "view/view.h"
#include "model/model.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

class ViewTest : public ::testing::Test {
protected:
    std::streambuf* orig;
    std::ostringstream out;

    void SetUp() override {
        orig = std::cout.rdbuf(out.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(orig);
    }
};

TEST_F(ViewTest, Update) {
    View view;
    Model model;

    view.update(model);

    ASSERT_EQ(out.str(), "View updated with model changes
");
}
