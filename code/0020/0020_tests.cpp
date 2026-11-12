#include "0020.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isValid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()"
true

"()[]{}"
true

"(]"
false

"([])"
true

"([)]"
false


)cases");

class t0020 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0020, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0020,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
