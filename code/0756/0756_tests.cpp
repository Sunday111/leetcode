#include "0756.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::pyramidTransition;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"BCD" ["BCC","CDE","CEA","FFF"] true

"AAAA" ["AAB","AAC","BCD","BBE","DEF"] false

"ABCD" ["ABC","BCA","CDA","ABD","BCE","CDF","DEA","EFF","AFF"] true
)cases");

using t0756 = SolutionTests<Solution>;

TEST_P(t0756, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.pyramidTransition(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0756,
    t0756::parameters(kCases.size()),
    t0756::name);
