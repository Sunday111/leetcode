#include "1096.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::braceExpansionII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"{a,b}{c,{d,e}}"        ["ac","ad","ae","bc","bd","be"]
"{{a,z},a{b,c},{ab,z}}" ["a","ab","ac","z"]
"{a,{c,d}}"             ["a","c","d"]
"abc"                   ["abc"]
"{a,aa}z"               ["aaz","az"]
"{b,a}{d,c}"            ["ac","ad","bc","bd"]
"{a,aa}{a,aa}"          ["aa","aaa","aaaa"]
"{{a,a},{a,b}}{b,b}"    ["ab","bb"]
"{{a,b}{c,d},a{c,d}}"   ["ac","ad","bc","bd"]
"{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}{a,aa}"
["aaaaaaaaaa","aaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaa","aaaaaaaaaaaaaa","aaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaa"]
"{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a}{a,a,a,a}{a,a,a,a}" ["aaaaaaaa"]
)");

using t1096 = SolutionTests<Solution>;

TEST_P(t1096, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.braceExpansionII(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1096,
    t1096::parameters(kCases.size()),
    t1096::name);
