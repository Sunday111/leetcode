#include <algorithm>

#include "0039_combination_sum.hpp"
#include "0039_combination_sum_2.hpp"
#include "0039_combination_sum_3.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::combinationSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,3,6,7] 7 [[2,2,3],[7]]

[38] 35 []
)");

using t0039_combination_sum = SolutionTests<Solution, Solution2, Solution3>;

TEST_P(t0039_combination_sum, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.combinationSum(args...); },
                inputs);
            ASSERT_EQ(sorted(expected), sorted(actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0039_combination_sum,
    t0039_combination_sum::parameters(kCases.size()),
    t0039_combination_sum::name);
