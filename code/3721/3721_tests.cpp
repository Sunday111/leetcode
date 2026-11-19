#include "3721.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, u32>(R"cases(
[2,5,4,3] 4
[3,2,2,5,4] 5
[1,2,3,2] 3
[19,5,41,39,39,23,20] 2
)cases");

using t3721 = SolutionTests<Solution>;
TEST_P(t3721, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            ASSERT_EQ(expected, solution.longestBalanced(std::get<0>(inputs)));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3721,
    t3721::parameters(kCases.size()),
    t3721::name);
