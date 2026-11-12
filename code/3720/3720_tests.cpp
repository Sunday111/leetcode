#include "3720.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::lexGreaterPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abc"
"bba"
"bca"

"leet"
"code"
"eelt"

"baba"
"bbaa"
""


)");

class t3720 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3720, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3720,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
