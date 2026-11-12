#include "0442.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findDuplicates;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,3,2,7,8,2,3,1] [2,3]
[1,1,2]           [1]
[1]               []
)");

class t0442 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0442, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0442,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
