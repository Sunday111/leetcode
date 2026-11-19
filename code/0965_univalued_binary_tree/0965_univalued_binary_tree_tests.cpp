#include "0965_univalued_binary_tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isUnivalTree;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,1,null,1] true

[1,100] false
)cases");

class t0965_univalued_binary_tree : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0965_univalued_binary_tree, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isUnivalTree(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0965_univalued_binary_tree,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
