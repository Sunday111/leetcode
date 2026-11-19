#include "1391.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::hasValidPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4,3],[6,5,2]] true
[[1,2,1],[1,2,1]] false
[[1,1,2]]         false
)");

using t1391 = SolutionTests<Solution>;

TEST_P(t1391, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.hasValidPath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1391,
    t1391::parameters(kCases.size()),
    t1391::name);
