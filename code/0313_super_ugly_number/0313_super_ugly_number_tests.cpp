#include "0313_super_ugly_number.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthSuperUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 [2,3,5] 12

1690 [2,3,5] 2123366400
)cases");

using t0313_super_ugly_number = SolutionTests<Solution>;

TEST_P(t0313_super_ugly_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.nthSuperUglyNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0313_super_ugly_number,
    t0313_super_ugly_number::parameters(kCases.size()),
    t0313_super_ugly_number::name);
