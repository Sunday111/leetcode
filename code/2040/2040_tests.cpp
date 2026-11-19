#include "2040.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>, u64>,
    i64>(R"cases(
[2,5] [3,4] 2 8
[-4,-2,0,3] [2,4] 6 0
)cases");

using t2040 = SolutionTests<Solution>;
TEST_P(t2040, Test)
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
    t2040,
    t2040::parameters(kCases.size()),
    t2040::name);
