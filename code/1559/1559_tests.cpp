#include "1559.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::containsCycle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]] true
[["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]] true
[["a","b","b"],["b","z","b"],["b","b","a"]] false
[["b","c","d","e","a","a","a"],["a","a","a","f","a","g","a"],["a","h","a","a","a","i","a"],["a","j","k","l","m","n","a"],["a","a","a","a","a","a","a"]] true
[["b","c","a","a"],["d","a","a","a"],["a","b","a","c"]] true
)");

class t1559 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1559, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1559,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
