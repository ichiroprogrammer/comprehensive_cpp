#pragma once
#include <condition_variable>
#include <future>
#include <mutex>
#include <string>

#include "dip_test_score.h"

namespace Solid_DIP_A {

// @@@ sample begin 0:0

class TestScoreClient : public TestScoreClientIF {
public:
    void             LoadAsync(std::string&& filename);
    virtual void     Done() override;
    void             Wait();
    TestScore const& GetTestScore() const noexcept { return test_score_; }

private:
    std::condition_variable condition_{};
    std::mutex              mutex_{};
    TestScore               test_score_{};
    TestScoreLoader         loader_{};
    bool                    loaded_{false};
};
// @@@ sample end
}  // namespace Solid_DIP_A
