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

// @@@ sample begin 1:0

class TestObserver : public Model::Observer {  // テスト用オブザーバー
public:
    void          Update(const Model& model) override { ++update_counter_; }
    std::uint32_t update_counter_ = 0;
};
// @@@ sample end

TEST(ModelTest, ExecAsync)
{
    // @@@ sample begin 1:1

    Model         model{};
    int           exec_counter{};
    TestObserver* to = new TestObserver;  // 下のunique_ptrで管理

    model.Attach(std::unique_ptr<TestObserver>{to});  // オブザーバの登録

    ASSERT_FALSE(model.IsBusy());  // ビジーでないことの確認

    model.ExecAsync([&exec_counter]() {  // 非同期要求のテスト開始
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });

    ASSERT_TRUE(model.IsBusy());        // ラムダ内で100ms待つため、ビジーとなる
    ASSERT_EQ(to->update_counter_, 0);  // まだラムダが実行されていないはず

    ASSERT_FALSE(model.ExecAsync([&exec_counter]() {  // まだラムダが実行されていないはず
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    }));

    model.Sync();  // 非同期要求の完了待ち
    ASSERT_EQ(exec_counter, 1);
    ASSERT_EQ(to->update_counter_, 1);  // オブザーバーのUpdateが呼ばれたことの確認

    model.ExecAsync([&exec_counter]() {
        ++exec_counter;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGGER("in ExecAsync");
    });
    // @@@ sample end

    ASSERT_TRUE(model.IsBusy());
    model.Sync();
    ASSERT_EQ(exec_counter, 2);
    ASSERT_EQ(to->update_counter_, 2);
    ASSERT_FALSE(model.IsBusy());
}
