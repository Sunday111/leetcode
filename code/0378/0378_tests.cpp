#include <algorithm>

#include "0378.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>, int>,
    int>(R"cases(
[[1,5,9],[10,11,13],[12,13,15]] 1 1
[[1,5,9],[10,11,13],[12,13,15]] 8 13
[[-5]] 1 -5
)cases");

using t0378 = SolutionTests<Solution>;
TEST_P(t0378, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [matrix, k] = inputs;
            ASSERT_EQ(expected, solution.kthSmallest(matrix, k));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0378,
    t0378::parameters(kCases.size()),
    t0378::name);
