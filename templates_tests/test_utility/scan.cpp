#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
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

TEST(ScannerTest, Vector)
{
    std::vector expected{1, 2, 3};
    ASSERT_EQ(expected, parse_from_string<std::vector<int>>(" [ 1 , 2 , 3 ] "));
}

TEST(ScannerTest, NestedVector)
{
    std::vector<std::vector<int>> expected{{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(
        expected,
        parse_from_string<std::vector<std::vector<int>>>(
            " [ [ 1 , 2 , 3 ] , [ 4 , 5 , 6 ] ] "));
}

TEST(ScannerTest, Tuple)
{
    auto expected = std::make_tuple(10, std::vector{1, 2, 3});
    auto actual = parse_from_string<std::tuple<int, std::vector<int>>>(
        " 10 [ 1 , 2 , 3 ] ");
    ASSERT_EQ(expected, actual);
}
