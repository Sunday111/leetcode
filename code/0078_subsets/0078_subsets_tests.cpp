#include <algorithm>

#include "0078_subsetstest_cases.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

class t0078_subsets : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0078_subsets, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    std::ranges::for_each(expected, std::ranges::sort);
    std::ranges::sort(expected);
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    std::ranges::for_each(actual, std::ranges::sort);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0078_subsets,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
