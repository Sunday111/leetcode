#include "2130_maximum_twin_sum_of_a_linked_listtest_cases.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static const auto kCases =
    parse_test_cases<kMethodToTest>(kTestCasesText);

class t2130_maximum_twin_sum_of_a_linked_list
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2130_maximum_twin_sum_of_a_linked_list, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    auto actual = Solution{}.pairSum(std::get<0>(inputs).head);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2130_maximum_twin_sum_of_a_linked_list,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
