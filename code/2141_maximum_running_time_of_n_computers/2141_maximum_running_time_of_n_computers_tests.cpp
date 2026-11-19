#include "2141_maximum_running_time_of_n_computers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRunTime;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [10,10,3,5] 8
)cases");

class t2141_maximum_running_time_of_n_computers
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2141_maximum_running_time_of_n_computers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxRunTime(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2141_maximum_running_time_of_n_computers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
