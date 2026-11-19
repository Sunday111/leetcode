#include <algorithm>
#include <print>

#include "0440_kth_smallest_in_lexicographical_order.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint64_t, uint64_t>, uint64_t>(
        R"cases(
13 2 10
1 1 1
100 10 17
)cases");

using t0440_kth_smallest_in_lexicographical_order = SolutionTests<Solution>;
TEST_P(t0440_kth_smallest_in_lexicographical_order, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto [n, k] = inputs;
            ASSERT_EQ(expected, solution.findKthNumber(n, k));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0440_kth_smallest_in_lexicographical_order,
    t0440_kth_smallest_in_lexicographical_order::parameters(kCases.size()),
    t0440_kth_smallest_in_lexicographical_order::name);
