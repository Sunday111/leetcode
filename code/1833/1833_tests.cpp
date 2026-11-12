#include "1833.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxIceCream;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2,4,1]     7 4
[10,6,8,7,7,8]  5 0
[1,6,3,1,2,5]  20 6
)");

class t1833 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1833, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1833,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
