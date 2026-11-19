#include "0015.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::threeSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,0,1,2,-1,-4] [[-1,-1,2],[-1,0,1]]

[0,1,1] []

[0,0,0] [[0,0,0]]
)");

using t0015 = SolutionTests<Solution>;

TEST_P(t0015, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.threeSum(args...); },
                inputs);
            ASSERT_EQ(sorted(expected), sorted(actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0015,
    t0015::parameters(kCases.size()),
    t0015::name);
