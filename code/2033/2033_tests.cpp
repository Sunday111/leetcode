#include "2033.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4],[6,8]] 2 4
[[1,5],[2,3]] 1 5
[[1,2],[3,4]] 2 -1
)");

class t2033 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2033, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2033,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
