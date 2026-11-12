#include "0010.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isMatch;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aa" "a*" true
"ab" ".*" true
"mississippi" "mis*is*ip*." true
"bbbba" ".*a*a" true
"a" ".*..a*" false
"baa" ".ba" false
"bbab" "b*a*" false
"bbba" ".*b" false
)");

class t0010 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0010, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0010,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
