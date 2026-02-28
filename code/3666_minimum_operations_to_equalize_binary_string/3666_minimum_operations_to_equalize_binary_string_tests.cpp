#include <tuple>

#include "3666_minimum_operations_to_equalize_binary_string.hpp"
#include "gtest/gtest.h"
#include "scan.hpp"
#include "test_cases.hpp"

// NOLINTNEXTLINE
static const auto kCases = parse_test_cases<std::string, u32, int>(kTestCases);

class T3666Test : public ::testing::TestWithParam<size_t>
{
};

TEST_P(T3666Test, MinOperations)
{
    const auto& [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto actual = std::apply(
        &Solution::minOperations,
        std::tuple_cat(std::make_tuple(&instance), inputs));
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    T3666Test,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
