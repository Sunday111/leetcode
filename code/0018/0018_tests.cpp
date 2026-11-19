#include "0018.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::fourSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,0,-1,0,-2,2] 0 [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

[2,2,2,2,2] 8 [[2,2,2,2]]

[0,0,0,0] 0 [[0,0,0,0]]

[-3,-1,0,2,4,5] 0 [[-3,-1,0,4]]

[1000000000,1000000000,1000000000,1000000000] 0 []

[0,4,-5,2,-2,4,2,-1,4] 12 [[0,4,4,4],[2,2,4,4]]
)");

using t0018_4sum = SolutionTests<Solution>;

TEST_P(t0018_4sum, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.fourSum(args...); },
                inputs);
            ASSERT_EQ(sorted(expected), sorted(actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0018_4sum,
    t0018_4sum::parameters(kCases.size()),
    t0018_4sum::name);
