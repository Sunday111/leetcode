#include "0065.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"32.e-80123" true
)cases");

using t0065 = SolutionTests<Solution>;

TEST_P(t0065, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0065,
    t0065::parameters(kCases.size()),
    t0065::name);
