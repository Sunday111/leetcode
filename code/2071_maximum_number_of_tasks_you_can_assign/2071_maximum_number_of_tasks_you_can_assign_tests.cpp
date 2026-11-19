#include "2071_maximum_number_of_tasks_you_can_assign.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>, u32, int>,
    int>(R"cases(
[3,2,1] [1,2,3] 1 1 3
[5,5,8,9,9] [1,2,4,6,6] 1 5 3
[1,2,3] [0,3,3] 1 1 3
)cases");

class t2071_maximum_number_of_tasks_you_can_assign
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2071_maximum_number_of_tasks_you_can_assign, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [tasks, workers, pills, strength] = inputs;
    ASSERT_EQ(
        expected,
        Solution{}.maxTaskAssign(tasks, workers, pills, strength));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2071_maximum_number_of_tasks_you_can_assign,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
