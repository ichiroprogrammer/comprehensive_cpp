#include <cassert>
#include <fstream>
#include <regex>
#include <sstream>

#include "lsp_test_score.h"

namespace Solid_LSP_Q {

// @@@ sample begin 0:0

namespace {
std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
{
    auto const csv_sep = std::regex{R"( *, *)"};
    auto       name    = std::string{};
    auto       score   = std::vector<int32_t>{};

    auto end = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end;
         ++it) {
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

bool is_valid_score(int32_t score) noexcept { return 0 <= score && score <= 100; }

bool not_score(int32_t score) noexcept { return score == -1; }
}  // namespace

void TestScore::validate_score(int32_t score) const
{
    if (is_valid_score(score) || not_score(score)) {
        return;
    }

    throw std::out_of_range{"Invalid Score"};
}

void TestScoreForce::validate_score(int32_t score) const
{
    if (is_valid_score(score)) {
        return;
    }

    throw std::out_of_range{"Invalid Score"};
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

void LoadCSV(std::string const& filename, TestScore& test_score)
{
    auto data = std::ifstream{filename};

    auto test_score_raw = TestScore::ScoreAll_t{};
    auto line           = std::string{};
    while (std::getline(data, line)) {
        // std::pair<TestScore::ScoreAll_t::iterator, bool>
        auto ret = test_score_raw.insert(parse_line(line));
        assert(ret.second);
    }

    auto one_test = TestScore::ScoreOne_t{};
    for (auto const& pair : test_score_raw) {
        one_test.emplace_back(std::make_pair(pair.first, 0));
    }

    auto const score_count = test_score_raw.begin()->second.size();
    auto       ts          = TestScore{};

    for (auto i = 0U; i < score_count; ++i) {
        for (auto& pair : one_test) {
            pair.second = test_score_raw[pair.first][i];
        }
        ts.AddScore(one_test);
    }

    test_score = std::move(ts);
}

void StoreCSV(TestScore const& test_score, std::string const& filename)
{
    auto data = std::ofstream{filename};
    auto ss   = std::ostringstream{};

    for (auto const& pair : test_score) {
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
        for (auto const s : pair.second) {
            ss << ' ' << s;
        }
        ss << std::endl;
    }

    return ss.str();
}

TestScore::ScoreOne_t Average(TestScore const& test_score)
{
    auto ret = TestScore::ScoreOne_t{};

    for (auto const& pair : test_score) {
        auto sum         = 0;
        auto valid_count = 0U;
        for (auto const s : pair.second) {
            if (is_valid_score(s)) {
                sum += s;
                ++valid_count;
            }
        }
        ret.emplace_back(std::make_pair(pair.first, valid_count == 0 ? -1 : sum / valid_count));
    }

    return ret;
}
// @@@ sample end
}  // namespace Solid_LSP_Q
