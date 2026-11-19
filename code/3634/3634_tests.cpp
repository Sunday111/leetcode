#include "3634.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, unsigned int>,
    unsigned int>(R"cases(
[2,1,5] 2 1

[1,6,2,9] 3 2

[4,6] 2 0

[1,34,23] 2 1
)cases");

using t3634 = SolutionTests<Solution>;

TEST_P(t3634, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3634,
    t3634::parameters(kCases.size()),
    t3634::name);
