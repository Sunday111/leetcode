#include "3314_construct_the_minimum_bitwise_array_i.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minBitwiseArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,3,5,7] [-1,1,4,3]

[11,13,31] [9,12,15]
)cases");

using t3314_construct_the_minimum_bitwise_array_i = SolutionTests<Solution>;

TEST_P(t3314_construct_the_minimum_bitwise_array_i, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minBitwiseArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3314_construct_the_minimum_bitwise_array_i,
    t3314_construct_the_minimum_bitwise_array_i::parameters(kCases.size()),
    t3314_construct_the_minimum_bitwise_array_i::name);
