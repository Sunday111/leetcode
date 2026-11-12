#include "1291.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sequentialDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
100
300
[123, 234]

1000
13000
[1234,2345,3456,4567,5678,6789,12345]
)");

class t1291 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1291, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1291,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
