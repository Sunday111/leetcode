#include <algorithm>
#include <print>

#include "0131.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string>,
    std::vector<std::vector<std::string>>>(R"cases(
"aab" [["a","a","b"],["aa","b"]]
"aaa" [["a","a","a"],["a","aa"],["aa","a"],["aaa"]]
)cases");

using t0131 = SolutionTests<Solution>;
TEST_P(t0131, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = solution.partition(std::get<0>(inputs));
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0131,
    t0131::parameters(kCases.size()),
    t0131::name);
