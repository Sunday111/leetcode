#include "3510_minimum_pair_removal_to_sort_array_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumPairRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,2,3,1] 2

[1,2,2] 0

[1,1,4,1] 2

[1,1,4,4,2,-4,-1] 5

[3,6,-9,6,3,-4] 4
)cases");

class t3510_minimum_pair_removal_to_sort_array_ii
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3510_minimum_pair_removal_to_sort_array_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumPairRemoval(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3510_minimum_pair_removal_to_sort_array_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
