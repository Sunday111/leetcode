#include "1945.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLucky;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"iiii" 1 36
)cases");

using t1945 = SolutionTests<Solution>;

TEST_P(t1945, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLucky(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1945,
    t1945::parameters(kCases.size()),
    t1945::name);
