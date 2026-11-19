#include "0324_wiggle_sort_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, std::vector<int>>(
        R"cases(
[1,5,1,1,6,4] [1,6,1,5,1,4]

[1,3,2,2,3,1] [2,3,1,3,1,2]
)cases");

using t0324_wiggle_sort_2 = SolutionTests<Solution>;

TEST_P(t0324_wiggle_sort_2, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            std::apply(
                [&](auto&... args) { return solution.wiggleSort(args...); },
                inputs);
            auto& actual = std::get<0>(inputs);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0324_wiggle_sort_2,
    t0324_wiggle_sort_2::parameters(kCases.size()),
    t0324_wiggle_sort_2::name);
