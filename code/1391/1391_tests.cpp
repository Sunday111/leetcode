#include "1391.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::hasValidPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4,3],[6,5,2]] true
[[1,2,1],[1,2,1]] false
[[1,1,2]]         false
)");

class t1391 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1391, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1391,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
