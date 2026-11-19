#include "1249.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minRemoveToMakeValid;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"lee(t(c)o)de)" "lee(t(c)o)de"

"a)b(c)d" "ab(c)d"

"))((" ""

"(a(b(c)d)" "a(b(c)d)"
)cases");

using t1249 = SolutionTests<Solution>;

TEST_P(t1249, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minRemoveToMakeValid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1249,
    t1249::parameters(kCases.size()),
    t1249::name);
