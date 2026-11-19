#include "3612.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::processStr;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"a#b%*"
"ba"

"z*#"
""


)");

using t3612 = SolutionTests<Solution>;

TEST_P(t3612, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.processStr(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3612,
    t3612::parameters(kCases.size()),
    t3612::name);
