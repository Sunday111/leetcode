#include "3823.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseByType;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
")ebc#da@f(" "(fad@cb#e)"

"!@#$%^&*()" ")(*&^%$#@!"
)cases");

using t3823 = SolutionTests<Solution>;

TEST_P(t3823, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reverseByType(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3823,
    t3823::parameters(kCases.size()),
    t3823::name);
