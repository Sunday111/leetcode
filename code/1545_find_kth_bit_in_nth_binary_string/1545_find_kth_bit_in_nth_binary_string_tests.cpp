#include "1545_find_kth_bit_in_nth_binary_string.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findKthBit;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 1 "0"

4 11 "1"

4 12 "0"

3 5 "0"

3 2 "1"

20 243002 "1"

20 189470 "0"

17 98304 "0"

20 426580 "1"

20 1048575 "1"

20 32944 "0"
)cases");

using t1545_find_kth_bit_in_nth_binary_string = SolutionTests<Solution>;

TEST_P(t1545_find_kth_bit_in_nth_binary_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findKthBit(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1545_find_kth_bit_in_nth_binary_string,
    t1545_find_kth_bit_in_nth_binary_string::parameters(kCases.size()),
    t1545_find_kth_bit_in_nth_binary_string::name);
