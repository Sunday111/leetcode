#include "1356_sort_integers_by_the_number_of_1_bits.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sortByBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,5,6,7,8] [0,1,2,4,8,3,5,6,7]

[1024,512,256,128,64,32,16,8,4,2,1] [1,2,4,8,16,32,64,128,256,512,1024]
)cases");

using t1356_sort_integers_by_the_number_of_1_bits = SolutionTests<Solution>;

TEST_P(t1356_sort_integers_by_the_number_of_1_bits, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sortByBits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1356_sort_integers_by_the_number_of_1_bits,
    t1356_sort_integers_by_the_number_of_1_bits::parameters(kCases.size()),
    t1356_sort_integers_by_the_number_of_1_bits::name);
