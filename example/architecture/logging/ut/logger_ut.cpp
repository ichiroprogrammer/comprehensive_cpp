#include <filesystem>

#include "gtest_wrapper.h"

#include "logging/logger.h"

namespace {

TEST(log, Logger)
{
    // loggingのテストは他のライブラリで行う。
    // ここではコンパイルできることの確認のみ。

    LOGGER_INIT(nullptr);
    LOGGER(1);
    LOGGER("xyz", 3, 5);

    auto file = std::filesystem::path{"hehe"};
    LOGGER(file);
}
}  // namespace
