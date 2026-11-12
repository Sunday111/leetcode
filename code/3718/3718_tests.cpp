#include "3718.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::missingMultiple;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[8,2,3,4,6]
2
10

[1,4,7,10,15]
5
5


)");

class t3718 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3718, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3718,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
