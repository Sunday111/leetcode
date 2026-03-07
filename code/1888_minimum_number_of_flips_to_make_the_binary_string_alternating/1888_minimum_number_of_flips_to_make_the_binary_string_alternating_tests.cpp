#include "1888_minimum_number_of_flips_to_make_the_binary_string_alternatingtest_cases.hpp"
#include "gtest/gtest.h"

class t1888_minimum_number_of_flips_to_make_the_binary_string_alternating : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1888_minimum_number_of_flips_to_make_the_binary_string_alternating, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1888_minimum_number_of_flips_to_make_the_binary_string_alternating,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
