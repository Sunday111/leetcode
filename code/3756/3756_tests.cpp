#include "3756.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumAndMultiply;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"10203004"
[[0,7],[1,3],[4,6]]
[12340, 4, 9]

"1000"
[[0,3],[1,1]]
[1, 0]

"9876543210"
[[0,9]]
[444444137]


)");

class t3756 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3756, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3756,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
