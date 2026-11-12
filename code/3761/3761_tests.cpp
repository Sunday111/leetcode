#include "3761.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minMirrorPairDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[12,21,45,33,54]
1

[120,21]
1

[21,120]
-1


)");

class t3761 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3761, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3761,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
