#include "0763.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::partitionLabels;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"ababcbacadefegdehijhklij"
[9,7,8]

"eccbbbbdec"
[10]
)");

using t0763 = SolutionTests<Solution>;

TEST_P(t0763, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.partitionLabels(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0763,
    t0763::parameters(kCases.size()),
    t0763::name);
