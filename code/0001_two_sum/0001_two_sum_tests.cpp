#include "0001_two_sum.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[2,7,11,15] 9 [0,1]
[3,2,4] 6 [1,2]
[3,3] 6 [0,1]
)");

using t0001_two_sum = SolutionTests<Solution>;

TEST_P(t0001_two_sum, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [nums, target] = inputs;
            auto actual = solution.twoSum(nums, target);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0001_two_sum,
    t0001_two_sum::parameters(kCases.size()),
    t0001_two_sum::name);
