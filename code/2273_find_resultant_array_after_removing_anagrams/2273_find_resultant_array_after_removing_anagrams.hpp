#pragma once

#include <algorithm>
#include <span>
#include <string>
#include <vector>

class Solution
{
public:
    static constexpr void getCounters(
        std::string_view s,
        const std::span<uint64_t, 4>& counters)
    {
        const std::span<uint8_t, 32> v{
            reinterpret_cast<uint8_t*>(&counters[0]),  // NOLINT
            32,
        };

        std::ranges::fill(counters, 0);
        for (char c : s) ++v[static_cast<uint8_t>(c - 'a')];
    }

    std::vector<std::string> removeAnagrams(std::vector<std::string>& words)
    {
        std::vector<std::string> r;
        r.reserve(words.size());

        uint8_t i = 0;
        const uint8_t n = static_cast<uint8_t>(words.size());
        std::array<uint64_t, 4> a{}, b{};

        while (i != n)
        {
            std::string& s = words[i++];
            getCounters(s, b);
            if (!std::ranges::equal(a, b))
            {
                r.push_back(std::move(s));
                std::ranges::copy(b, a.begin());
            }
        }

        return r;
    }
};
