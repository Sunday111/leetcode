#include "2977_minimum_cost_to_convert_string_ii.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumCost;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcdefgh" "acdeeghh" ["bcd","fgh","thh"] ["cde","thh","ghh"] [1,3,5] 9
)cases");

using t2977_minimum_cost_to_convert_string_ii = SolutionTests<Solution>;

TEST_P(t2977_minimum_cost_to_convert_string_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2977_minimum_cost_to_convert_string_ii,
    t2977_minimum_cost_to_convert_string_ii::parameters(kCases.size()),
    t2977_minimum_cost_to_convert_string_ii::name);
