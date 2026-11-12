#include "1665.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumEffort;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2],[2,4],[4,8]] 8
[[1,3],[2,4],[10,11],[10,12],[8,9]] 32
[[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]] 27
)");

class t1665 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1665, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1665,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
