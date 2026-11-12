#include "1331.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::arrayRankTransform;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[40,10,20,30] [4,1,2,3]
[100,100,100] [1,1,1]
[37,12,28,9,100,56,80,5,12] [5,3,4,2,8,6,7,1,3]
)");

class t1331 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1331, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1331,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
