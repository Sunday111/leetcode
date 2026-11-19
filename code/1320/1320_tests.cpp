#include "1320.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"CAKE" 3
"HAPPY" 6
"OPVUWZLCKTDPSUKGHAXIDWHLZFKNBDZEWHBSURTVCADUGTSDMCLDBTAGFWDPGXZBVARNTDICHCUJLNFBQOBTDWMGILXPSFWVGYBZVFFKQIDTOVFAPVNSQJULMVIERWAOXCKXBRI" 295
)");

using t1320 = SolutionTests<Solution>;

TEST_P(t1320, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1320,
    t1320::parameters(kCases.size()),
    t1320::name);
