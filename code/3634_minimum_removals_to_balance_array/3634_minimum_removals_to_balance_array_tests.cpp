#include "3634_minimum_removals_to_balance_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int>,
    unsigned int>(R"cases(
[2,1,5] 2 1

[1,6,2,9] 3 2

[4,6] 2 0

[1,34,23] 2 1
)cases");

using t3634_minimum_removals_to_balance_array = SolutionTests<Solution>;

TEST_P(t3634_minimum_removals_to_balance_array, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3634_minimum_removals_to_balance_array,
    t3634_minimum_removals_to_balance_array::parameters(kCases.size()),
    t3634_minimum_removals_to_balance_array::name);
