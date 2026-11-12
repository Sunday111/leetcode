#include "3020.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumLength;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[12,12,144,144,20736,20736,429981696,429981696] 7
[16,16,256,256,65536,65536]                     5
[5,4,1,2,2]                                     3
[1,3,2,4]                                       1
[1,1]                                           1
[4,36,9,16,1,1,4,121,64,4]                      3
)");

class t3020 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3020, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3020,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
