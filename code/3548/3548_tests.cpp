#include "3548_test_cases.hpp"
#include "gtest/gtest.h"

class t3548 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3548, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);

    EXPECT_EQ(expected, actual);

    if (expected != actual)
    {
        std::println("Input matrix:");
        for (auto& row : std::get<0>(inputs))
        {
            std::print("    ");
            for (auto v : row)
            {
                std::print("{:4} ", v);
            }
            std::println("");
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3548,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
