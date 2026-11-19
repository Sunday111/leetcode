#include "3003_maximize_the_number_of_partitions_after_operations.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPartitionsAfterOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"accca" 2 3

"aabaab" 3 1

"xxyz" 1 4

"bbbbcbcbbc" 2 3
)cases");

class t3003_maximize_the_number_of_partitions_after_operations
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3003_maximize_the_number_of_partitions_after_operations, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.maxPartitionsAfterOperations(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3003_maximize_the_number_of_partitions_after_operations,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
