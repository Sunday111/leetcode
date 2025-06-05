#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> findWordsContaining(
        const std::vector<std::string>& words,
        char x) noexcept
    {
        std::vector<int> r;
        r.reserve(words.size());

        for (size_t i = 0; i != words.size(); ++i)
        {
            const auto& word = words[i];
            if (auto it = std::ranges::find(word, x); it != word.end())
            {
                r.push_back(static_cast<int>(i));
            }
        }

        return r;
    }
};
