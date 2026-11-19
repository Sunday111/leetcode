#include "1823.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint16_t, uint16_t>, uint16_t>(
        R"cases(
5 2 3
6 5 1
1 1 1
)cases");

using t1823 = SolutionTests<Solution>;
TEST_P(t1823, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto [n, k] = inputs;
            ASSERT_EQ(expected, solution.findTheWinner(n, k));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1823,
    t1823::parameters(kCases.size()),
    t1823::name);
