#include "3003.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPartitionsAfterOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"accca" 2 3

"aabaab" 3 1

"xxyz" 1 4

"bbbbcbcbbc" 2 3
)cases");

using t3003 = SolutionTests<Solution>;

TEST_P(t3003, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxPartitionsAfterOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3003,
    t3003::parameters(kCases.size()),
    t3003::name);
