#include "1503_last_momemnt_before_all_ants_fall_out_of_a_plank.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLastMoment;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 [4,3] [0,1] 4
)cases");

class t1503_last_momemnt_before_all_ants_fall_out_of_a_plank
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1503_last_momemnt_before_all_ants_fall_out_of_a_plank, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.getLastMoment(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1503_last_momemnt_before_all_ants_fall_out_of_a_plank,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
