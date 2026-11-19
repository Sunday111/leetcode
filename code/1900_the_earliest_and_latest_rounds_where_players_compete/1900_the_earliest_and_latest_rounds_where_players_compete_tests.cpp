#include "1900_the_earliest_and_latest_rounds_where_players_compete.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::earliestAndLatest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
11 2 4 [3,4]

5 1 5 [1,1]
)cases");

class t1900_the_earliest_and_latest_rounds_where_players_compete
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1900_the_earliest_and_latest_rounds_where_players_compete, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.earliestAndLatest(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1900_the_earliest_and_latest_rounds_where_players_compete,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
