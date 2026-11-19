#include "1022_sum_of_root_to_leaf_binary_numbers.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<convert_expected_type_t<TreeNode*>>,
    unsigned int>(R"cases(
[1,0,1,0,1,0,1] 22
)cases");

class t1022_sum_of_root_to_leaf_binary_numbers
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1022_sum_of_root_to_leaf_binary_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.sumRootToLeaf(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1022_sum_of_root_to_leaf_binary_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
