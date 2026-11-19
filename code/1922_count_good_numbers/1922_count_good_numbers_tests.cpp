#include "1922_count_good_numbers.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countGoodNumbers;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 5

4 400

50 564908303

806166225460393 643535977
)cases");

using t1922_count_good_numbers = SolutionTests<Solution>;

TEST_P(t1922_count_good_numbers, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countGoodNumbers(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1922_count_good_numbers,
    t1922_count_good_numbers::parameters(kCases.size()),
    t1922_count_good_numbers::name);
