#include "1123.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lcaDeepestLeaves;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,5,1,6,2,0,8,null,null,7,4] [2,7,4]
)cases");

using t1123 = SolutionTests<Solution>;

TEST_P(t1123, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.lcaDeepestLeaves(args...); },
                inputs);
            ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1123,
    t1123::parameters(kCases.size()),
    t1123::name);
