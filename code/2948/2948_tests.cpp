#include "2948.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexicographicallySmallestArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,5,3,9,8] 2 [1,3,5,8,9]
[1,7,6,18,2,1] 3 [1,6,7,18,1,2]
[1,7,28,19,10] 3 [1,7,28,19,10]
)");

class t2948 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2948, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2948,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
