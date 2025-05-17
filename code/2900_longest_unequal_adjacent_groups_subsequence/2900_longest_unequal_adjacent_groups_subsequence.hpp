#pragma once

#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr std::vector<std::string> getLongestSubsequence(
        std::vector<std::string>& words,
        std::vector<int>& groups)
    {
        std::vector<std::string> r;
        r.reserve(words.size() / 2);
        r.emplace_back(std::move(words.front()));

        for (size_t i = 1; i != words.size(); ++i)
        {
            if (groups[i] != groups[i - 1]) r.push_back(std::move(words[i]));
        }

        return r;
    }
};
