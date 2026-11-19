#include "2014.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<std::tuple<std::string, u16>, std::string>(R"cases(
"letsleetcode" 2 "let"
"bb" 2 "b"
"ab" 2 ""
"nhsbbeonhsbbeonhsbbeo" 3 "nhsbbeo"
"gbjbjigjbji" 2 "gjbji"
)cases");

using t2014 = SolutionTests<Solution3>;
TEST_P(t2014, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [s, k] = inputs;
            ASSERT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
        });
}
INSTANTIATE_TEST_SUITE_P(Gen, t2014, t2014::parameters(kCases.size()), t2014::name);
