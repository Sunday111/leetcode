#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

TEST(ScannerTest, WhitespaceAtEnd)
{
    DefaultScannerOptions options;
    EXPECT_EQ(skip_whitespaces(options, "", 0), 0);
    EXPECT_EQ(skip_whitespaces(options, " \t\n", 0), 3);
    EXPECT_EQ(skip_whitespaces(options, "x \t\n", 1), 4);
    EXPECT_EQ(skip_whitespaces(options, "x", 1), 1);
    EXPECT_EQ(skip_whitespaces(options, " x", 0), 1);
}

TEST(ScannerTest, EmptyAndTrailingWhitespaceCases)
{
    using Inputs = std::tuple<int>;
    EXPECT_TRUE((parse_test_cases_with_types<Inputs, int>("").empty()));
    EXPECT_TRUE((parse_test_cases_with_types<Inputs, int>(" \t\n").empty()));
    for (std::string_view input : {"1 2", "1 2 \t\n"})
    {
        auto cases = parse_test_cases_with_types<Inputs, int>(input);
        ASSERT_EQ(cases.size(), 1);
        EXPECT_EQ(std::get<0>(std::get<0>(cases.front())), 1);
        EXPECT_EQ(std::get<1>(cases.front()), 2);
    }
}
