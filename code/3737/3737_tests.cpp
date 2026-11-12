#include "3737.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countMajoritySubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,2,3]
2
5

[1,1,1,1]
1
10

[1,2,3]
4
0


)");

class t3737 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3737, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3737,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
