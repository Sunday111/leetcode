#include "1970_last_day_where_you_can_still_cross.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::latestDayToCross;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 2 [[1,1],[2,1],[1,2],[2,2]] 2
)cases");

class t1970_last_day_where_you_can_still_cross
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1970_last_day_where_you_can_still_cross, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.latestDayToCross(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1970_last_day_where_you_can_still_cross,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
