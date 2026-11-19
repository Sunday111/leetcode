#include "2616.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int>,
    unsigned int>(R"cases(
[10,1,2,7,1,3] 2 1

[4,2,1,2] 1 0

[1,2000,2001,2002,3002,4000,4002,5000,6000,6003,10000] 4 998

[3,4,2,3,2,1,2] 3 1
)cases");

using t2616 = SolutionTests<Solution>;

TEST_P(t2616, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimizeMax(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2616,
    t2616::parameters(kCases.size()),
    t2616::name);
