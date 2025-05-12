#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string_view digits)
    {
        if (digits.empty())
        {
            return {};
        }

        std::vector<std::string> combinations;
        combinations.reserve(128);

        constexpr std::array<std::string_view, 8> idx_to_letter{
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"};

        std::vector<int> indices;
        indices.reserve(digits.size());
        indices.push_back(-1);

        while (!indices.empty())
        {
            {
                int& last_index = indices.back();
                ++last_index;
                const std::string_view& letters =
                    idx_to_letter[std::bit_cast<unsigned>(
                        digits[indices.size() - 1] - '2')];
                if (std::cmp_greater_equal(last_index, letters.size()))
                {
                    indices.pop_back();
                    continue;
                }
            }

            indices.resize(digits.size(), 0);

            std::string& combination = combinations.emplace_back();
            combination.reserve(digits.size());

            for (size_t idxidx = 0; idxidx != indices.size(); ++idxidx)
            {
                const char digit = digits[idxidx];
                const char letter =
                    idx_to_letter[std::bit_cast<unsigned>(digit - '2')]
                                 [std::bit_cast<unsigned>(indices[idxidx])];
                combination += letter;
            }
        }

        return combinations;
    }
};
