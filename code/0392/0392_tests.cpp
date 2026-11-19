#include "0392.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aaaaaa" "bbaaaa" false

"abc" "ahbgdc" true

"axc" "ahbgdc" false
)cases");

using t0392 = SolutionTests<Solution>;

TEST_P(t0392, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0392,
    t0392::parameters(kCases.size()),
    t0392::name);
