#include "3633.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::earliestFinishTime;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,8]
[4,1]
[6]
[3]
9

[5]
[3]
[1]
[10]
14


)");

class t3633 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3633, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3633,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
