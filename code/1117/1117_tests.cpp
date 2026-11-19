#include <algorithm>
#include <thread>

#include "1117.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, size_t>(R"cases(
"HOH" 1
"OOHHHH" 2
"HHHOHO" 2
)cases");

class t1117 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1117, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [input] = inputs;
    std::string output(input.size(), '?');
    std::atomic<size_t> position{0};
    H2O water;
    {
        std::vector<std::jthread> threads;
        for (char c : input)
        {
            threads.emplace_back(
                [&, c]
                {
                    auto release = [&]
                    {
                        output[position.fetch_add(1)] = c;
                    };
                    if (c == 'H')
                        water.hydrogen(release);
                    else
                        water.oxygen(release);
                });
        }
    }
    ASSERT_EQ(position.load(), expected * 3);
    for (size_t i = 0; i < output.size(); i += 3)
    {
        auto molecule = output.substr(i, 3);
        std::ranges::sort(molecule);
        ASSERT_EQ(molecule, "HHO");
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1117,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
