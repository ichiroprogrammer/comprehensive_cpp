#include <cassert>
#include <fstream>
#include <regex>
#include <sstream>

#include "srp_test_score.h"

namespace Solid_SRP_Q {

// @@@ sample begin 0:0

namespace {
std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
{
    auto const csv_sep = std::regex{R"( *, *)"};
    auto       name    = std::string{};
    auto       score   = std::vector<int32_t>{};

    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
        if (name.length() == 0) {
            name = *it;
        }
        else {
            auto s = std::stoi(*it);
            score.emplace_back(s);
        }
    }

    return {std::move(name), std::move(score)};
}
}  // namespace

void TestScore::validate_score(int32_t score) const
{
    auto highest = 100;
    auto lowest  = 0;
    auto invalid = -1;

    if (lowest <= score && score <= highest) {
        ;  // do notihng
    }
    else if (invalid == score) {
        ;  // do notihng
    }
    else {
        throw std::out_of_range{"Invalid Score"};
    }
}

void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
{
    for (auto const& pair : one_test_score) {
        validate_score(pair.second);
    }

    if (test_score_row_.size() == 0) {
        test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
    }

    for (auto& pair : test_score_row_) {
        pair.second.push_back(-1);
    }

    auto curr_test_count = test_score_row_.begin()->second.size();

    for (auto const& pair : one_test_score) {
        if (test_score_row_.find(pair.first) == test_score_row_.end()) {
            test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
        }

        test_score_row_[pair.first].back() = pair.second;
    }
}

void TestScore::LoadCSV(std::string const& filename)
{
    auto data = std::ifstream{filename};

    auto test_score_raw = ScoreAll_t{};
    auto line           = std::string{};
    while (std::getline(data, line)) {
        // std::pair<TestScore::ScoreAll_t::iterator, bool>
        auto ret = test_score_raw.insert(parse_line(line));
        assert(ret.second);
    }

    for (auto const& pair : test_score_raw) {
        for (auto const s : pair.second) {
            validate_score(s);
        }
    }

    test_score_row_.swap(test_score_raw);
}

void TestScore::StoreCSV(std::string const& filename) const
{
    auto data = std::ofstream{filename};
    auto ss   = std::ostringstream{};

    for (auto const& pair : test_score_row_) {
        ss << pair.first;
        for (auto const s : pair.second) {
            ss << ", " << s;
        }
        ss << std::endl;
    }

    data << ss.str();
}

std::string ToString(TestScore const& ts)
{
    auto ss = std::ostringstream{};

    for (auto const& pair : ts) {
        ss << pair.first << ':';
        for (auto const& s : pair.second) {
            ss << ' ' << s;
        }
        ss << std::endl;
    }

    return ss.str();
}
// @@@ sample end
}  // namespace Solid_SRP_Q
