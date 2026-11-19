#include "2163.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int64_t>(R"cases(
[3,1,2] -1
)cases");

using t2163 = SolutionTests<all_branches::Solution>;
TEST_P(t2163, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            ASSERT_EQ(
                expected,
                solution.minimumDifference(std::get<0>(inputs)));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2163,
    t2163::parameters(kCases.size()),
    t2163::name);
