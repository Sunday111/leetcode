#include <cassert>

#include "0124_binary_tree_maximum_path_sum.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPathSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 6

[-10,9,20,null,null,15,7] 42

[-2,-1] -1
)cases");

class t0124_binary_tree_maximum_path_sum
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0124_binary_tree_maximum_path_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxPathSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0124_binary_tree_maximum_path_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
