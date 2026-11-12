#include "2946.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::areSimilar;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,5,6],[7,8,9]]
4
false

[[1,2,1,2],[5,5,5,5],[6,3,6,3]]
2
true

[[2,2],[2,2]]
3
true


)");

class t2946 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2946, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2946,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
