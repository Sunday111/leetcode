#include "1008.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::bstFromPreorder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[8,5,1,7,10,12] [8,5,10,1,7,null,12]
)cases");

using t1008 = SolutionTests<Solution>;

TEST_P(t1008, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.bstFromPreorder(args...); },
                inputs);
            const bool equal = CompareBinaryTrees(expected.root, actual);
            DeleteBinaryTree(actual);
            ASSERT_TRUE(equal);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1008,
    t1008::parameters(kCases.size()),
    t1008::name);
