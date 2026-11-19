#include "0165.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::compareVersion;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1.2" "1.10" -1

"1.0.1" "1" 1
)cases");

using t0165 = SolutionTests<Solution>;

TEST_P(t0165, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.compareVersion(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0165,
    t0165::parameters(kCases.size()),
    t0165::name);
