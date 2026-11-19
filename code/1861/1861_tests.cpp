#include "1861.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotateTheBox;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
    [["#",".","#"]]
    [["."],["#"],["#"]]

    [["#",".","*","."],["#","#","*","."]]
    [["#","."],
     ["#","#"],
     ["*","*"],
     [".","."]]

    [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]]
    [[".","#","#"],
     [".","#","#"],
     ["#","#","*"],
     ["#","*","."],
     ["#",".","*"],
     ["#",".","."]]
)");

using t1861 = SolutionTests<Solution>;

TEST_P(t1861, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.rotateTheBox(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1861,
    t1861::parameters(kCases.size()),
    t1861::name);
