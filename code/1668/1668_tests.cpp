#include "1668.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRepeating;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"ababc" "ab" 2

"ababc" "ba" 1

"ababc" "ac" 0

"aaabaaaabaaabaaaabaaaabaaaabaaaaba" "aaaba" 5
)cases");

using t1668 = SolutionTests<Solution>;

TEST_P(t1668, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRepeating(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1668,
    t1668::parameters(kCases.size()),
    t1668::name);
