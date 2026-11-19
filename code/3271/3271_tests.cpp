#include "3271.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::stringHash;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bf"

"mxz" 3 "i"

"hcr" 3 "a"
)cases");

using t3271 = SolutionTests<Solution>;

TEST_P(t3271, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stringHash(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3271,
    t3271::parameters(kCases.size()),
    t3271::name);
