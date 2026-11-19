#include "2081.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint8_t, uint8_t>, uint64_t>(R"cases(
2 5 25
3 7 499
7 17 20379000
)cases");

#ifndef NDEBUG
using t2081 = SolutionTests<Solution, Cheat, Solution2, Solution3, Solution4>;
#else
using t2081 = SolutionTests<Solution, Cheat>;
#endif

TEST_P(t2081, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.kMirror(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2081,
    t2081::parameters(kCases.size()),
    t2081::name);
