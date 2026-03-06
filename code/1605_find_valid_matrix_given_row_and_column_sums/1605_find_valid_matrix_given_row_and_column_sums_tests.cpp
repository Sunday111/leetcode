#include "1605_find_valid_matrix_given_row_and_column_sumstest_cases.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

class t1605_find_valid_matrix_given_row_and_column_sums
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1605_find_valid_matrix_given_row_and_column_sums, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1605_find_valid_matrix_given_row_and_column_sums,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
