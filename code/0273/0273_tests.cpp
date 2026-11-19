#include "0273.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberToWords;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
123 "One Hundred Twenty Three"

12345 "Twelve Thousand Three Hundred Forty Five"

1234567 "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

1234567891
"One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
)cases");

using t0273 = SolutionTests<Solution>;

TEST_P(t0273, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberToWords(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0273,
    t0273::parameters(kCases.size()),
    t0273::name);
