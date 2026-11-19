#include "1461.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::hasAllCodes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"00110110" 2 true

"0110" 1 true

"0110" 2 false

"00110" 2 true
)cases");

using t1461 = SolutionTests<Solution>;

TEST_P(t1461, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.hasAllCodes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1461,
    t1461::parameters(kCases.size()),
    t1461::name);
