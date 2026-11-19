#include "2948.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexicographicallySmallestArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,5,3,9,8] 2 [1,3,5,8,9]
[1,7,6,18,2,1] 3 [1,6,7,18,1,2]
[1,7,28,19,10] 3 [1,7,28,19,10]
)");

using t2948 = SolutionTests<Solution>;

TEST_P(t2948, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lexicographicallySmallestArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2948,
    t2948::parameters(kCases.size()),
    t2948::name);
