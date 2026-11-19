#include "1582.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numSpecial;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,0,0],[0,0,1],[1,0,0]]
1

[[1,0,0],[0,1,0],[0,0,1]]
3

)");

using t1582 = SolutionTests<Solution>;

TEST_P(t1582, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numSpecial(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1582,
    t1582::parameters(kCases.size()),
    t1582::name);
