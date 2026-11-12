#include "2029.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameIX;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,1]           true
[2]             false
[5,1,2,4,3]     false
[20,3,20,17,2,12,15,17,4] true
)");

class t2029 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2029, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2029,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
