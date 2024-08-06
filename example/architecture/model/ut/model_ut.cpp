#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

#include "gtest/gtest.h"
#include "logging/logger.h"
#include "model/model.h"

TEST(ModelTest, AAA_FistTest)
{
    LOGGER_INIT("log.txt");  // logging用のファイルの初期化
}

class TestObserver : public Model::Observer {
public:
    void          Update(const Model& model) override { ++update_counter_; }
    std::uint32_t update_counter_ = 0;
};

TEST(ModelTest, ExecAsync)
{
    Model         model{};
    int           exec_counter{};
    TestObserver* to = new TestObserver;

    model.Attach(std::unique_ptr<TestObserver>{to});

    ASSERT_FALSE(model.IsBusy());

    model.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });

    ASSERT_TRUE(model.IsBusy());
    ASSERT_EQ(to->update_counter_, 0);

    ASSERT_FALSE(model.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    }));

    model.Sync();
    ASSERT_EQ(exec_counter, 1);
    ASSERT_EQ(to->update_counter_, 1);

    model.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });

    ASSERT_TRUE(model.IsBusy());
    model.Sync();
    ASSERT_EQ(exec_counter, 2);
    ASSERT_EQ(to->update_counter_, 2);
    ASSERT_FALSE(model.IsBusy());
}
