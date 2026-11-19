#include <algorithm>

#include "0039.hpp"
#include "0039_2.hpp"
#include "0039_3.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::combinationSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,3,6,7] 7 [[2,2,3],[7]]

[38] 35 []
)");

using t0039 = SolutionTests<Solution, Solution2, Solution3>;

TEST_P(t0039, Test)
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
    t0039,
    t0039::parameters(kCases.size()),
    t0039::name);
