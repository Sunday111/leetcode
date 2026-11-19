#include "3321_find_xsum_of_all_klong_subarrays_ii.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int, unsigned int>,
    std::vector<long long>>(R"cases(
[1,1,2,2,3,4,2,3] 6 2 [6,10,12]
)cases");

using t3321_find_xsum_of_all_klong_subarrays_ii = SolutionTests<Solution>;

TEST_P(t3321_find_xsum_of_all_klong_subarrays_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findXSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3321_find_xsum_of_all_klong_subarrays_ii,
    t3321_find_xsum_of_all_klong_subarrays_ii::parameters(kCases.size()),
    t3321_find_xsum_of_all_klong_subarrays_ii::name);
