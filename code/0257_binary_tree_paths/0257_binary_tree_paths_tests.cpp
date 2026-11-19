#include "0257_binary_tree_paths.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryTreePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,null,5] ["1->2->5","1->3"]
)cases");

class t0257_binary_tree_paths : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0257_binary_tree_paths, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.binaryTreePaths(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0257_binary_tree_paths,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
