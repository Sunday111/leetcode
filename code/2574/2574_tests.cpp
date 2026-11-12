#include "2574.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::leftRightDifference;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,4,8,3] [15,1,11,22]
[1] [0]
)");

class t2574 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2574, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2574,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
