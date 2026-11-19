#include <algorithm>

#include "1233.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeSubfolders;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["/a","/a/b","/c/d","/c/d/e","/c/f"] ["/a","/c/d","/c/f"]

["/a","/a/b/c","/a/b/d"] ["/a"]

["/a/b/c","/a/b/ca","/a/b/d"] ["/a/b/c","/a/b/ca","/a/b/d"]

["/aa/ab/ac/ae","/aa/ab/af/ag","/ap/aq/ar/as","/ap/aq/ar","/ap/ax/ay/az","/ap","/ap/aq/ar/at","/aa/ab/af/ah","/aa/ai/aj/ak","/aa/ai/am/ao"]
["/aa/ab/ac/ae","/aa/ab/af/ag","/aa/ab/af/ah","/aa/ai/aj/ak","/aa/ai/am/ao","/ap"]
)cases");

using t1233 = SolutionTests<Solution>;

TEST_P(t1233, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.removeSubfolders(args...); },
                inputs);
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1233,
    t1233::parameters(kCases.size()),
    t1233::name);
