#pragma once
#include <filesystem>

#include "gtest_wrapper.h"

namespace Solid_UT {
// @@@ sample begin 0:0

class SolidFixture : public ::testing::Test {
protected:
    std::string const test_score_org_     = "../ut_data2/test_score_org.csv";
    std::string const test_score_org_f_   = "../ut_data2/test_score_org_f.csv";
    std::string const test_score_act_     = "../ut_data2/test_score_act.csv";
    std::string const test_score_exp_     = "../ut_data2/test_score_exp.csv";
    std::string const test_score_exp_err_ = "../ut_data2/test_score_exp_err.csv";

    virtual void SetUp() noexcept override { remove_file(test_score_act_); }
    virtual void TearDown() noexcept override { remove_file(test_score_act_); }

    static void remove_file(std::string const& filename) noexcept
    {
        if (std::filesystem::exists(filename)) {
            std::filesystem::remove(filename);
        }
    }
};

// clang-format off
class SolidSRP_Q : public SolidFixture {};
class SolidOCP_Q : public SolidFixture {};
class SolidLSP_Q : public SolidFixture {};
class SolidISP_Q : public SolidFixture {};
class SolidDIP_Q : public SolidFixture {};

class SolidSRP_A : public SolidFixture {};
class SolidOCP_A : public SolidFixture {};
class SolidLSP_A : public SolidFixture {};
class SolidISP_A : public SolidFixture {};
class SolidDIP_A : public SolidFixture {};
// clang-format on
// @@@ sample end
}  // namespace Solid_UT
