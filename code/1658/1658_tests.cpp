#include "1658.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,4,2,3]         5       2
[5,6,7,8,9]         4       -1
[3,2,20,1,1,3]      10      5
[1,1]               3       -1
[5,2,3,1,1]         5       1
[2,3,1,1,1]         5       2
[1000,1,1,2,3]      1004    3
)");

class t1658 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1658, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1658,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
