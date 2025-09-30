#include <fstream>
#include <regex>
#include <sstream>

#include "isp_test_score.h"
#include "isp_test_score_average.h"

namespace Solid_ISP_A {

// @@@ sample begin 0:0

namespace {

TestScore::ScoreOne_t get_average(std::string const& filename)
{
    TestScore ts = LoadCSV(filename);

    return Average(ts);
}
}  // namespace

struct TestScoreAverage::TestScoreAverageData {
    TestScoreAverageData(TestScore::ScoreOne_t&& average) : average{std::move(average)} {}

    TestScore::ScoreOne_t const average;
    std::vector<std::string>    desending_order{};
};

TestScoreAverage::TestScoreAverage(std::string const& filename)
    : data_{std::make_unique<TestScoreAverage::TestScoreAverageData>(get_average(filename))}
{
}

TestScoreAverage::~TestScoreAverage() = default;  // これはヘッダには書けない

uint32_t TestScoreAverage::GetAverage(std::string const& name) const
{
    auto pos
        = std::find_if(data_->average.cbegin(), data_->average.cend(),
                       [&name](std::pair<std::string, int32_t> const& pair) noexcept { return name == pair.first; });

    if (pos == data_->average.cend()) {
        throw std::out_of_range{"no member"};
    }

    return pos->second;
}

std::vector<std::string> const& TestScoreAverage::DescendingOrder() const
{
    if (data_->desending_order.size() != 0) {
        return data_->desending_order;
    }

    auto ave = data_->average;
    std::sort(ave.begin(), ave.end(), [](std::pair<std::string, int32_t> const& lhs, auto const& rhs) noexcept {
        return lhs.second > rhs.second;
    });

    for (auto& pair : ave) {
        data_->desending_order.emplace_back(std::move(pair.first));
    }

    return data_->desending_order;
}
// @@@ sample end
}  // namespace Solid_ISP_A
