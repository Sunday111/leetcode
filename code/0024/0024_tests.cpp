#include "0024.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::swapPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4] [2,1,4,3]
)");

using t0024 = SolutionTests<Solution>;

TEST_P(t0024, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.swapPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0024,
    t0024::parameters(kCases.size()),
    t0024::name);
