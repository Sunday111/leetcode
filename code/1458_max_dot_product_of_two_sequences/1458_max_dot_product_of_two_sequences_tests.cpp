#include "1458_max_dot_product_of_two_sequences.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxDotProduct;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,1,-2,5] [3,0,-6] 18

[3,-2] [2,-6,7] 21

[-1,-1] [1,1] -1

[-3,-8,3,-10,1,3] [9,2,3,7,-9,1,5] 133

[-3,-8,3,-10,1,3,9] [9,2,3,7,-9,1,-8,5,-1,-1] 200

[-3,-8,-10] [7,-9,-8] 152
)cases");

using t1458_max_dot_product_of_two_sequences = SolutionTests<Solution>;

TEST_P(t1458_max_dot_product_of_two_sequences, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxDotProduct(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1458_max_dot_product_of_two_sequences,
    t1458_max_dot_product_of_two_sequences::parameters(kCases.size()),
    t1458_max_dot_product_of_two_sequences::name);
