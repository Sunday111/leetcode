#include "0096_unique_binary_search_trees.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numTrees;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1

2 2

3 5

4 14

5 42

6 132

7 429

8 1430

19 1767263190
)cases");

class t0096_unique_binary_search_trees : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0096_unique_binary_search_trees, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numTrees(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0096_unique_binary_search_trees,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
