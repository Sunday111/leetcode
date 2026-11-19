#include "2106_maximum_fruits_harvested_after_at_most_k_steps.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>, u32, u32>,
    u32>(R"cases(
[[2,8],[6,3],[8,6]] 5 4 9
[[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]] 5 4 14
[[0,3],[6,4],[8,5]] 3 2 0
[[0,10000]] 200000 200000 10000
)cases");

class t2106_maximum_fruits_harvested_after_at_most_k_steps
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2106_maximum_fruits_harvested_after_at_most_k_steps, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [fruits, start, k] = inputs;
    ASSERT_EQ(expected, Solution{}.maxTotalFruits(fruits, start, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2106_maximum_fruits_harvested_after_at_most_k_steps,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
