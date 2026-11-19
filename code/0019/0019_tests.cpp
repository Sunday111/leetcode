#include <cassert>

#include "0019.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeNthFromEnd;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4,5] 2 [1,2,3,5]
)");

using t0019 = SolutionTests<Solution>;

TEST_P(t0019, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.removeNthFromEnd(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0019,
    t0019::parameters(kCases.size()),
    t0019::name);
