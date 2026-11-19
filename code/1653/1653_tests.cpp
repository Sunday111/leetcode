#include "1653.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeletions;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aababbab" 2

"bbaaaaabb" 2
)cases");

using t1653 = SolutionTests<Solution>;

TEST_P(t1653, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDeletions(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1653,
    t1653::parameters(kCases.size()),
    t1653::name);
