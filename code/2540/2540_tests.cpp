#include "2540.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getCommon;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3]
[2,4]
2
[1,2,3,6]
[2,3,4,5]
2
)");

using t2540 = SolutionTests<Solution>;

TEST_P(t2540, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getCommon(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2540,
    t2540::parameters(kCases.size()),
    t2540::name);
