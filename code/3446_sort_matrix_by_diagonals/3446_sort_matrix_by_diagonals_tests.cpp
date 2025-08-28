#include "3446_sort_matrix_by_diagonals.hpp"
#include "gtest/gtest.h"

std::vector<std::vector<int>> parse2DArray(std::string_view input)
{
    std::vector<std::vector<int>> result;
    std::vector<int> currentRow;
    std::stringstream numberBuffer;

    for (char c : input)
    {
        if (isdigit(c) || c == '-')
        {
            numberBuffer << c;  // collect digits (and minus for negatives)
        }
        else
        {
            if (!numberBuffer.str().empty())
            {
                currentRow.push_back(std::stoi(numberBuffer.str()));
                numberBuffer.str("");
                numberBuffer.clear();
            }
            if (c == ']')
            {
                if (!currentRow.empty())
                {
                    result.push_back(currentRow);
                    currentRow.clear();
                }
            }
        }
    }
    return result;
}

struct TestCase
{
    std::string_view input;
    std::string_view expected;
};

TEST(t3446_sort_matrix_by_diagonals, test_1)
{
    std::vector<TestCase> test_cases{
        {
            .input = "[[1,7,3],[9,8,2],[4,5,6]]",
            .expected = "[[8,2,3],[9,6,7],[4,5,1]]",
        },
    };

    for (auto& test_case : test_cases)
    {
        auto grid = parse2DArray(test_case.input);
        auto actual = Solution{}.sortMatrix(grid);
        auto expected = parse2DArray(test_case.expected);
        EXPECT_EQ(actual, expected);

        auto print2DArray =
            [](std::string_view title, const std::vector<std::vector<int>>& a)
        {
            std::println("{}:", title);
            for (auto& row : a)
            {
                std::print("    ");
                for (auto& v : row) std::print("{:2}", v);
                std::println();
            }
        };

        if (actual != expected)
        {
            grid = parse2DArray(test_case.input);
            print2DArray("Input", grid);
            print2DArray("Actual:", actual);
            print2DArray("Expected:", expected);
        }
    }
}
