#include "cast/cast.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "unknown_001_maximum_sum.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<u32>>, u32>,
    u32>(R"cases(
[[33,99],[33,99],[33,99]] 5 363
[[3,7,2],[4,1,5]] 3 15
[[4]] 1 4
)cases");

class tunknown_001_maximum_sum : public ::testing::TestWithParam<size_t>
{
};
TEST_P(tunknown_001_maximum_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [rows, k] = inputs;
    std::vector<u32> data;
    for (auto& row : rows) data.insert(data.end(), row.begin(), row.end());
    MatrixView<const u32> matrix{
        data.data(),
        cast<u32>(rows.size()),
        cast<u32>(rows.front().size())};
    ASSERT_EQ(expected, Solution{}.maximumSumBrute(matrix, k));
    ASSERT_EQ(expected, Solution{}.maximumSumMemo(matrix, k));
    ASSERT_EQ(expected, Solution{}.maximumSum(matrix, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    tunknown_001_maximum_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
