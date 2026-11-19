#include "0865.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::subtreeWithAllDeepest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,5,1,6,2,0,8,null,null,7,4] [2,7,4]

[1] [1]

[0,1,3,null,2] [2]

[0,2,1,null,null,3] [3]
)cases");

using t0865 = SolutionTests<Solution>;

TEST_P(t0865, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.subtreeWithAllDeepest(args...); },
                inputs);
            ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0865,
    t0865::parameters(kCases.size()),
    t0865::name);
