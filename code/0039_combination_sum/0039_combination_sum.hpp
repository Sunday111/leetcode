#pragma once

#include <bit>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int32_t>> combinationSum(
        std::vector<int32_t>& candidates_,
        int32_t target)
    {
        const auto t = static_cast<uint8_t>(target);

        std::array<std::vector<std::string>, 50> number_to_paths;

        for (auto ic : candidates_)
        {
            auto c = static_cast<char>(ic);
            number_to_paths[std::bit_cast<uint8_t>(c)].push_back({c});
            for (char i = c + 1; i <= t; ++i)  // NOLINT
            {
                auto& paths_to_prev =
                    number_to_paths[std::bit_cast<unsigned>(i - c)];
                if (paths_to_prev.empty()) continue;

                auto& paths_to_i = number_to_paths[std::bit_cast<uint8_t>(i)];
                paths_to_i.reserve(paths_to_prev.size());
                for (const auto& p : paths_to_prev)
                {
                    paths_to_i.emplace_back(p).push_back(c);
                }
            }
        }

        const auto& r = number_to_paths[t];

        std::vector<std::vector<int32_t>> result;
        result.reserve(r.size());

        for (const auto& p : r)
        {
            auto& dest = result.emplace_back();
            dest.reserve(p.size());
            for (auto c : p)
            {
                dest.push_back(c);
            }
        }

        return result;
    }
};
