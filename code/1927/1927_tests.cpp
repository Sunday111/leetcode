#include "1927.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumGame;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"5023"                                                                      false
"25??"                                                                      true
"?3295???"                                                                  false
"?6?6?000?3"                                                                true
"?0?3105????1834??7382?997?3?????7?63116?566?701?065?13?3??38?7?488?????9"  false
"??????"                                                                    false
"81??"                                                                      false
"0009??"                                                                    true
)");

using t1927 = SolutionTests<Solution>;

TEST_P(t1927, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumGame(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1927,
    t1927::parameters(kCases.size()),
    t1927::name);
