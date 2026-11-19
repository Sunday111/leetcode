#include "0067.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addBinary;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11" "1" "100"

"1010" "1011" "10101"
)cases");

using t0067 = SolutionTests<Solution>;

TEST_P(t0067, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.addBinary(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0067,
    t0067::parameters(kCases.size()),
    t0067::name);
