#include "3551.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSwaps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,1,2]
2

[18,43,34,16]
2

[22,14,33,7]
0

[37,100]
1

)");

class t3551 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3551, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3551,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
