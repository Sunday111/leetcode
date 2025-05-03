#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

using Group = std::vector<std::string>;
using Groups = std::vector<Group>;

class Solution
{
public:
    template <size_t extent>
    static constexpr size_t spanHash(std::span<uint8_t, extent> s)
    {
        size_t hash = 14695981039346656037ULL;
        for (uint8_t c : s)
        {
            hash = (hash ^ c) * 1099511628211ULL;
        }
        return hash;
    }

    struct StringInfo
    {
        std::array<uint8_t, 26> char_counts{};
        size_t hash{};
    };

    Groups groupAnagrams(std::vector<std::string>& strings)
    {
        Groups groups;
        groups.reserve(strings.size());

        constexpr auto hasher = [](const StringInfo& info)
        {
            return info.hash;
        };

        constexpr auto comparator = [](const StringInfo& a, const StringInfo& b)
        {
            return std::ranges::equal(a.char_counts, b.char_counts);
        };

        std::unordered_map<
            StringInfo,
            size_t,
            decltype(hasher),
            decltype(comparator)>
            info_to_group_index;
        info_to_group_index.reserve(strings.size());

        for (size_t i = 0; i != strings.size(); ++i)
        {
            auto& s = strings[i];

            StringInfo info;
            for (char c : s)
            {
                ++info.char_counts[std::bit_cast<unsigned>(c - 'a')];
            }
            info.hash = spanHash(std::span{info.char_counts});

            auto it = info_to_group_index.find(info);
            if (it != info_to_group_index.end())
            {
                groups[it->second].push_back(std::move(s));
            }
            else
            {
                const size_t group_index = groups.size();
                groups.emplace_back(std::vector{std::move(s)});
                info_to_group_index[info] = group_index;
            }
        }

        return groups;
    }
};
