#pragma once

#include <bitset>
#include <string>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr int maxProduct(
        const std::vector<std::string>& words) noexcept
    {
        const auto n = static_cast<u16>(words.size());
        std::array<std::bitset<32>, 1001> letters;
        // For each word prepare bitset with letters
        for (u16 i = 0; i != n; ++i)
        {
            auto& li = letters[i];
            for (auto c : words[i]) li[(c - 'a') & 0xFF] = 1;
        }

        // Do an N^N lookup for maximum value
        int r = 0;
        for (u16 i = 0; i != n; ++i)
        {
            auto& li = letters[i];
            for (u16 j = i + 1; j != n; ++j)
            {
                if (auto lj = letters[j]; !(li & lj).count())
                {
                    r = std::max(
                        r,
                        static_cast<int>(words[i].size() * words[j].size()));
                }
            }
        }
        return r;
    }
};
