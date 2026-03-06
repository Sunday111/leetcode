#include "____problem_name____test_cases.hpp"
#include "gtest/gtest.h"

class t____problem_name____ : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t____problem_name____, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t____problem_name____,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
