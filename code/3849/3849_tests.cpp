#include "3849.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumXor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"101"
"011"
"110"

"0110"
"1110"
"1101"

"0101"
"1001"
"1111"


)");

class t3849 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3849, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3849,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
