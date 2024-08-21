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
    // @@@ sample begin 1:0

    std::ostringstream out;
    View view{};

    ViewCore::Inst().SetOStream(out);   // 出力の切り替え
    const auto* str = "Output string to View";

    view.ShowAsync(str);    // 非同期出力
    view.Sync();            // 出力待ち
    ASSERT_EQ(out.str(), str);
    // @@@ sample end
}
