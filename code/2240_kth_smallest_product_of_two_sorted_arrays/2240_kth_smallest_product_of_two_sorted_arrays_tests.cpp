#include "2240_kth_smallest_product_of_two_sorted_arrays.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>, u64>,
    i64>(R"cases(
[2,5] [3,4] 2 8
[-4,-2,0,3] [2,4] 6 0
)cases");

using t2240_kth_smallest_product_of_two_sorted_arrays = SolutionTests<Solution>;
TEST_P(t2240_kth_smallest_product_of_two_sorted_arrays, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [a, b, k] = inputs;
            ASSERT_EQ(expected, solution.kthSmallestProduct(a, b, k));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2240_kth_smallest_product_of_two_sorted_arrays,
    t2240_kth_smallest_product_of_two_sorted_arrays::parameters(kCases.size()),
    t2240_kth_smallest_product_of_two_sorted_arrays::name);
