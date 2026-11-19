#include "3440_reschedule_meetings_for_maximum_free_time_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFreeTime;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 [1,3] [2,5] 2

37 [5,14,27,34] [13,18,31,37] 16

20 [2,4,6,9,18] [4,6,9,16,20] 4
)cases");

class t3440_reschedule_meetings_for_maximum_free_time_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3440_reschedule_meetings_for_maximum_free_time_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxFreeTime(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3440_reschedule_meetings_for_maximum_free_time_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
