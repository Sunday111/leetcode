#include "0628.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-2,-1,3,4,5]               60
[0,-1,0,-2,-1,1]            2
[-2,-3,-1,0,-8]             0
[-7,-2,2,-1,-4]             56
[1,-2,2,-12,-17]            408
[-1,-2,-3,5,-4]             60
[-9,2,-10,5,-3,8,-7,4,-1]   720
[-1,-2,-3]                  -6
[-1,-2,-3,-4]               -6
)");

class t0628 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0628, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0628,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
