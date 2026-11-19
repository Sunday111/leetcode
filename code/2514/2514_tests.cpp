#include "2514.hpp"
#include "integral_aliases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, u32>(R"cases(
"too hot" 18
"b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp" 210324488
)cases");

using t2514 = SolutionTests<Solution, CachingFactorialsSolution>;

TEST_P(t2514, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countAnagrams(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2514,
    t2514::parameters(kCases.size()),
    t2514::name);
