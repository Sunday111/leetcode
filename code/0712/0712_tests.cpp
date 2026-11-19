#include "0712.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeleteSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"sea" "eat" 231

"delete" "leet" 403
)cases");

using t0712 = SolutionTests<Solution>;

TEST_P(t0712, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDeleteSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0712,
    t0712::parameters(kCases.size()),
    t0712::name);
