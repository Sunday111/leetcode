#include "3517.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestPalindrome;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"z"
"z"

"babab"
"abbba"

"daccad"
"acddca"


)");

class t3517 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3517, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3517,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
