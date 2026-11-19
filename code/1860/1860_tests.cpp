#include "1860.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::memLeak;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
8 11 [6,0,4]

2 2 [3,1,0]

2147483647 2147483647 [92681,88047,41707]
)cases");

using t1860 = SolutionTests<Solution>;

TEST_P(t1860, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.memLeak(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1860,
    t1860::parameters(kCases.size()),
    t1860::name);
