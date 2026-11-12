#include "2615.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::distance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,1,1,2] [5,0,3,4,0]
[0,5,3]     [0,0,0]
)");

class t2615 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2615, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2615,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
