#include "3335.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lengthAfterTransformations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcyy" 2 7

"azbk" 5 5
)cases");

using t3335 = SolutionTests<Solution>;

TEST_P(t3335, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lengthAfterTransformations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3335,
    t3335::parameters(kCases.size()),
    t3335::name);
