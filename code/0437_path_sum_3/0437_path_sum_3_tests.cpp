#include "0437_path_sum_3.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<convert_expected_type_t<TreeNode*>, int>,
    int>(R"cases(
[10,5,-3,3,2,null,11,3,-2,null,1] 8 3

[5,4,8,11,null,13,4,7,2,null,null,5,1] 22 3
)cases");

class t0437_path_sum_3 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0437_path_sum_3, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.pathSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0437_path_sum_3,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
