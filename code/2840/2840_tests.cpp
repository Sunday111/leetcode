#include "2840.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcdba"
"cabdab"
true

"abe"
"bea"
false
)");

class t2840 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2840, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2840,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
