#include "0061.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[1,2,3,4,5]
2
[4,5,1,2,3]

[0,1,2]
4
[2,0,1]
)");

using t0061 = SolutionTests<Solution>;

TEST_P(t0061, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [vals, k] = inputs;
            auto in_list = LeetCodeList<ListNode>::FromArray(std::span{vals});
            auto expected_list =
                LeetCodeList<ListNode>::FromArray(std::span{expected});
            auto out = solution.rotateRight(in_list.head, k);
            ASSERT_TRUE(CompareLists(expected_list.head, out));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0061,
    t0061::parameters(kCases.size()),
    t0061::name);
