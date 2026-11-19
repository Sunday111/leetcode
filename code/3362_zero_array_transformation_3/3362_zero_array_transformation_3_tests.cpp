#include "3362_zero_array_transformation_3.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,0,2] [[0,2],[0,2],[1,1]] 1

[1,2,3,4] [[0,3]] -1

[0,3] [[0,0],[0,0],[0,1],[0,1],[0,1]] 2
)cases");

class t3362_zero_array_transformation_3
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3362_zero_array_transformation_3, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxRemoval(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3362_zero_array_transformation_3,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
