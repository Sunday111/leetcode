#include "3130.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfStableArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
1
2
2

1
2
1
1

3
3
2
14

460
397
305
381281021

)");

using t3130 = SolutionTests<Solution>;

TEST_P(t3130, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfStableArrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3130,
    t3130::parameters(kCases.size()),
    t3130::name);
