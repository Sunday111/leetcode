#include "0097.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isInterleave;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aabcc" "dbbca" "aadbbcbcac" true

"aabcc" "dbbca" "aadbbbaccc" false

"ab" "bc" "babc" true
)cases");

using t0097 = SolutionTests<Solution>;

TEST_P(t0097, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isInterleave(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0097,
    t0097::parameters(kCases.size()),
    t0097::name);
