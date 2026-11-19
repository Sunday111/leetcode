#include "3408_design_task_manager.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    std::vector<int>>(R"cases(
[] [-1]
[[1,101,10],[2,102,20],[3,103,15]] [2,3,1,-1]
)cases");

class t3408_design_task_manager : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t3408_design_task_manager, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [tasks] = inputs;
    TaskManager manager(tasks);
    for (int user : expected) ASSERT_EQ(manager.execTop(), user);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3408_design_task_manager,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
