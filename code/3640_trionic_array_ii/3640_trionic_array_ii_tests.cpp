#include "3640_trionic_array_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSumTrionic;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,-2,-1,-3,0,2,-1] -4

[1,4,2,7] 14
)cases");

class t3640_trionic_array_ii : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3640_trionic_array_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxSumTrionic(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3640_trionic_array_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
