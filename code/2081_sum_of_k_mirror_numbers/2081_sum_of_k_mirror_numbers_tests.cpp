#include "2081_sum_of_k_mirror_numbers.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint8_t, uint8_t>, uint64_t>(R"cases(
2 5 25
3 7 499
7 17 20379000
)cases");

#ifndef NDEBUG
using t2081_sum_of_k_mirror_numbers =
    SolutionTests<Solution, Cheat, Solution2, Solution3, Solution4>;
#else
using t2081_sum_of_k_mirror_numbers = SolutionTests<Solution, Cheat>;
#endif

TEST_P(t2081_sum_of_k_mirror_numbers, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.kMirror(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2081_sum_of_k_mirror_numbers,
    t2081_sum_of_k_mirror_numbers::parameters(kCases.size()),
    t2081_sum_of_k_mirror_numbers::name);
