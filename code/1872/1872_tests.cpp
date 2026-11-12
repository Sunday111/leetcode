#include "1872.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameVIII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[7,-6,5,10,5,-2,-6] 13
[-1,2,-3,4,-5] 5
)");

class t1872 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1872, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1872,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
