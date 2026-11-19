#include <algorithm>

#include "0078.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::subsets;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3]
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
)");

using t0078 = SolutionTests<Solution>;

TEST_P(t0078, MinOperations)
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
    t0078,
    t0078::parameters(kCases.size()),
    t0078::name);
