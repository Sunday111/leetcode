#include "0065_valid_number.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"32.e-80123" true
)cases");

using t0065_valid_number = SolutionTests<Solution>;

TEST_P(t0065_valid_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0065_valid_number,
    t0065_valid_number::parameters(kCases.size()),
    t0065_valid_number::name);
