#include "0437.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<convert_expected_type_t<TreeNode*>, int>,
    int>(R"cases(
[10,5,-3,3,2,null,11,3,-2,null,1] 8 3

[5,4,8,11,null,13,4,7,2,null,null,5,1] 22 3
)cases");

using t0437 = SolutionTests<Solution>;

TEST_P(t0437, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.pathSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0437,
    t0437::parameters(kCases.size()),
    t0437::name);
