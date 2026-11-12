#include "0153.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMin;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] 1
[4,5,6,7,0,1,2] 0
[11,13,15,17] 11
)");

class t0153 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0153, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0153,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
