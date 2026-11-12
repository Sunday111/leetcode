#include "3689.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxTotalValue;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2]
2
4

[4,2,5,1]
3
12


)");

class t3689 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3689, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3689,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
