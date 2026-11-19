#include "0018_4sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::fourSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,0,-1,0,-2,2] 0 [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

[2,2,2,2,2] 8 [[2,2,2,2]]

[0,0,0,0] 0 [[0,0,0,0]]

[-3,-1,0,2,4,5] 0 [[-3,-1,0,4]]

[1000000000,1000000000,1000000000,1000000000] 0 []

[0,4,-5,2,-2,4,2,-1,4] 12 [[0,4,4,4],[2,2,4,4]]
)");

class t0018_4sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0018_4sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.fourSum(args...); },
        inputs);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0018_4sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
