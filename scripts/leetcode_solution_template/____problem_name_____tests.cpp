#include "____problem_name____.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::____method_name____;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
____test_data____
)");

class t____problem_name____ : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t____problem_name____, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t____problem_name____,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
