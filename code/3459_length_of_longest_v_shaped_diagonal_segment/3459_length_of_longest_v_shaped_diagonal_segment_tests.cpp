#include "3459_length_of_longest_v_shaped_diagonal_segment.hpp"
#include "gtest/gtest.h"

std::vector<std::vector<int>> parse2DArray(const std::string& input)
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

TEST(t3459_length_of_longest_v_shaped_diagonal_segment, test_1)
{
    std::vector<std::pair<std::string, int>> cases{
        {"[[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]", 5},
        {"[[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]", 4},
        {"[[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]", 5},
        {"[[1]]", 1},
        {"[[2,0],[0,1]]", 2},
        {"[[1,2,0,0],[0,0,1,2]]", 2},
    };

    for (size_t i = 0; i != cases.size(); ++i)
    {
        const auto& [str, expected] = cases[i];
        const auto grid = parse2DArray(str);
        EXPECT_EQ(Solution{}.lenOfVDiagonal(grid), expected) << "Case " << i;
    }
}
