#include "3761.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minMirrorPairDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[12,21,45,33,54]
1

[120,21]
1

[21,120]
-1


)");

using t3761 = SolutionTests<Solution>;

TEST_P(t3761, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minMirrorPairDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3761,
    t3761::parameters(kCases.size()),
    t3761::name);
