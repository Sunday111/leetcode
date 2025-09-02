#pragma once

#include <sstream>
#include <string_view>
#include <vector>

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
