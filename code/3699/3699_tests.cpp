#include "3699.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::zigZagArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
4
5
2

3
1
3
10

4
1
5
170

)");

using t3699 = SolutionTests<Solution>;

TEST_P(t3699, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.zigZagArrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3699,
    t3699::parameters(kCases.size()),
    t3699::name);
