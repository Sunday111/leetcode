#include "2977.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumCost;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcdefgh" "acdeeghh" ["bcd","fgh","thh"] ["cde","thh","ghh"] [1,3,5] 9
)cases");

using t2977 = SolutionTests<Solution>;

TEST_P(t2977, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2977,
    t2977::parameters(kCases.size()),
    t2977::name);
