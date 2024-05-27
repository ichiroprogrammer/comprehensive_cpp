#include "dip_test_score_client.h"

namespace Solid_DIP_A {

// @@@ sample begin 0:0

// 演習コードと同一であるため省略
// @@@ ignore begin

void TestScoreClient::LoadAsync(std::string&& filename)
{
    loader_.LoadCSV_Async(std::move(filename), *this);
}

void TestScoreClient::Done()
{
    {
        auto lock = std::lock_guard{mutex_};
        loaded_   = true;
    }

    condition_.notify_all();
}

void TestScoreClient::Wait()
{
    auto lock = std::unique_lock{mutex_};

    condition_.wait(lock, [&loaded = loaded_]() noexcept { return loaded; });

    test_score_ = loader_.LoadCSV_Get();
}
// @@@ ignore end

// @@@ sample end
}  // namespace Solid_DIP_A
