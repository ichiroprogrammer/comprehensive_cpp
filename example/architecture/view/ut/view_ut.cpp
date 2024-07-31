#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/model.h"
#include "view/view.h"

class ViewTest : public ::testing::Test {
protected:
    std::streambuf*    orig;
    std::ostringstream out;

    void SetUp() override
    {
        orig = std::cout.rdbuf(out.rdbuf());
        LOGGER_INIT("log.txt");  // logging用のファイルの初期化
    }

    void TearDown() override { std::cout.rdbuf(orig); }
};

TEST_F(ViewTest, AAA_FistTest) {}

TEST_F(ViewTest, Update)
{
    std::ostringstream out;

    View view{out};

    const auto* str = "View updated with model changes";

    view.ShowAsync(str);
    view.Sync();
    ASSERT_EQ(out.str(), str);
}
