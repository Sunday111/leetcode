#include "3025_find_the_number_of_ways_to_place_people_1.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0],[0,3]] 1

[[1,1],[2,2],[3,3]] 0

[[3,1],[1,3],[1,1]] 2
)cases");

using t3025_find_the_number_of_ways_to_place_people_1 = SolutionTests<Solution>;

TEST_P(t3025_find_the_number_of_ways_to_place_people_1, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3025_find_the_number_of_ways_to_place_people_1,
    t3025_find_the_number_of_ways_to_place_people_1::parameters(kCases.size()),
    t3025_find_the_number_of_ways_to_place_people_1::name);
