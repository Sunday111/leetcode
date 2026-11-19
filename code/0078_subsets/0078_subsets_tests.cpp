#include <algorithm>

#include "0078_subsetstest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t0078_subsets = SolutionTests<Solution>;

TEST_P(t0078_subsets, MinOperations)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            std::ranges::for_each(expected, std::ranges::sort);
            std::ranges::sort(expected);
            auto actual = solution.subsets(std::get<0>(inputs));
            std::ranges::for_each(actual, std::ranges::sort);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0078_subsets,
    t0078_subsets::parameters(kCases.size()),
    t0078_subsets::name);
