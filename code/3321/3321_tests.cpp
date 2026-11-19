#include "3321.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int, unsigned int>,
    std::vector<long long>>(R"cases(
[1,1,2,2,3,4,2,3] 6 2 [6,10,12]
)cases");

using t3321 = SolutionTests<Solution>;

TEST_P(t3321, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findXSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3321,
    t3321::parameters(kCases.size()),
    t3321::name);
