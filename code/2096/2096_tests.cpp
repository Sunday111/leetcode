#include "2096.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getDirections;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,1,2,3,null,6,4] 3 6 "UURL"
)cases");

using t2096 = SolutionTests<Solution>;

TEST_P(t2096, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getDirections(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2096,
    t2096::parameters(kCases.size()),
    t2096::name);
