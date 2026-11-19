#include "1022.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<convert_expected_type_t<TreeNode*>>,
    unsigned int>(R"cases(
[1,0,1,0,1,0,1] 22
)cases");

using t1022 = SolutionTests<Solution>;

TEST_P(t1022, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumRootToLeaf(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1022,
    t1022::parameters(kCases.size()),
    t1022::name);
