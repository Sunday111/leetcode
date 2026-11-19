#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

#include "1409.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::processQueries;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,1,2,1] 5 [2,1,2,1]

[4,4,4,4] 4 [3,0,0,0]
)cases");

using t1409 = SolutionTests<Solution>;

TEST_P(t1409, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            const auto original = inputs;
            auto actual = std::apply(
                [&](auto&... args) { return solution.processQueries(args...); },
                inputs);
            ASSERT_EQ(expected, actual);
            ASSERT_EQ(original, inputs);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1409,
    t1409::parameters(kCases.size()),
    t1409::name);
