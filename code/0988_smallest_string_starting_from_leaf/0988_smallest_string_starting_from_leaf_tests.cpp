#include "0988_smallest_string_starting_from_leaf.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestFromLeaf;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,3,4] "dba"

[25,1,3,1,3,0,2] "adz"

[25,0,null,1,null,0,0,1,null,null,null,0] "ababaz"
)cases");

class t0988_smallest_string_starting_from_leaf
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0988_smallest_string_starting_from_leaf, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.smallestFromLeaf(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0988_smallest_string_starting_from_leaf,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
