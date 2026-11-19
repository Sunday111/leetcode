#include "0015_3sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::threeSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,0,1,2,-1,-4] [[-1,-1,2],[-1,0,1]]

[0,1,1] []

[0,0,0] [[0,0,0]]
)");

class t0015_3sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0015_3sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.threeSum(args...); },
        inputs);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0015_3sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
