#include "dip_test_score_client.h"

namespace Solid_DIP_Q {

// @@@ sample begin 0:0

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

    condition_.wait(lock, [&loaded = loaded_] { return loaded; });

    test_score_ = loader_.LoadCSV_Get();
}
// @@@ sample end
}  // namespace Solid_DIP_Q
