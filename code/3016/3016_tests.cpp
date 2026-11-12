#include "3016.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumPushes;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcde"                     5
"xyzxyzxyzxyz"              12
"aabbccddeeffgghhiiiiii"    24
)");

class t3016 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3016, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3016,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
