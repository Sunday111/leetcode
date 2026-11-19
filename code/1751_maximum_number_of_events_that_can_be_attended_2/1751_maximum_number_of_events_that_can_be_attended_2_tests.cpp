#include "1751_maximum_number_of_events_that_can_be_attended_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxValue;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,4],[3,4,3],[2,3,1]] 2 7

[[1,2,4],[3,4,3],[2,3,10]] 2 10

[[1,1,1],[2,2,2],[3,3,3],[4,4,4]] 3 9
)cases");

class t1751_maximum_number_of_events_that_can_be_attended_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1751_maximum_number_of_events_that_can_be_attended_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxValue(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1751_maximum_number_of_events_that_can_be_attended_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
