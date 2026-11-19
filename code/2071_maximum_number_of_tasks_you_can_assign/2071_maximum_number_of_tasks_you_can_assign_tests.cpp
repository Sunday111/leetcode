#include "2071_maximum_number_of_tasks_you_can_assign.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>, u32, int>,
    int>(R"cases(
[3,2,1] [1,2,3] 1 1 3
[5,5,8,9,9] [1,2,4,6,6] 1 5 3
[1,2,3] [0,3,3] 1 1 3
)cases");

using t2071_maximum_number_of_tasks_you_can_assign = SolutionTests<Solution>;
TEST_P(t2071_maximum_number_of_tasks_you_can_assign, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [tasks, workers, pills, strength] = inputs;
            ASSERT_EQ(
                expected,
                solution.maxTaskAssign(tasks, workers, pills, strength));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2071_maximum_number_of_tasks_you_can_assign,
    t2071_maximum_number_of_tasks_you_can_assign::parameters(kCases.size()),
    t2071_maximum_number_of_tasks_you_can_assign::name);
