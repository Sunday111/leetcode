#include "1498.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>, u32>, u32>(R"cases(
[3,5,6,7] 9 4
[5,2,4,1,7,6,8] 16 127
)cases");

using t1498 = SolutionTests<Solution>;
TEST_P(t1498, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [nums, target] = inputs;
            ASSERT_EQ(expected, solution.numSubseq(nums, target));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1498,
    t1498::parameters(kCases.size()),
    t1498::name);
