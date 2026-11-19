#include "0001.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[2,7,11,15] 9 [0,1]
[3,2,4] 6 [1,2]
[3,3] 6 [0,1]
)");

using t0001 = SolutionTests<Solution>;

TEST_P(t0001, Test)
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
    t0001,
    t0001::parameters(kCases.size()),
    t0001::name);
