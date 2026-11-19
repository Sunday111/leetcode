#include "2553.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::separateDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[13,25,83,77] [1,3,2,5,8,3,7,7]
[7,1,3,9]     [7,1,3,9]
)");

using t2553 = SolutionTests<Solution>;

TEST_P(t2553, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.separateDigits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2553,
    t2553::parameters(kCases.size()),
    t2553::name);
