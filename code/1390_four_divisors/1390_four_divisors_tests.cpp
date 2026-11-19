#include "1390_four_divisors.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sumFourDivisors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[31911,85919,25557,9951,3936,88317,71321,74651,88416,34378] 289182
)cases");

using t1390_four_divisors = SolutionTests<Solution>;

TEST_P(t1390_four_divisors, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumFourDivisors(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1390_four_divisors,
    t1390_four_divisors::parameters(kCases.size()),
    t1390_four_divisors::name);
