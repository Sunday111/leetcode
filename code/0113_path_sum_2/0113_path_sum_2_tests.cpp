#include "0113_path_sum_2.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryTreePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,4,8,11,null,13,4,7,2,null,null,5,1] 22 [[5,4,11,2],[5,8,4,5]]
)cases");

class t0113_path_sum_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0113_path_sum_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.binaryTreePaths(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0113_path_sum_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
