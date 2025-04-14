#pragma once

#include <bit>
#include <bitset>
#include <cassert>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

class Solution
{
public:
    using Bitset = std::bitset<25>;

    [[nodiscard]] static std::tuple<uint8_t, uint8_t> countOrphans(
        const std::string_view& s,
        Bitset view)
    {
        uint8_t num_open = 0;
        uint8_t num_closed = 0;

        uint8_t i = 0;

        auto next_idx = [&]
        {
            i = static_cast<uint8_t>(
                std::countr_zero(static_cast<uint32_t>(view.to_ulong())));
            if (i < s.size())
            {
                view[i] = false;
                return true;
            }

            return false;
        };

        while (next_idx())
        {
            switch (s[i])
            {
            case '(':
                ++num_open;
                break;

            case ')':
                if (num_open)
                {
                    --num_open;
                }
                else
                {
                    ++num_closed;
                }
                break;
            }

            ++i;
        }

        return {num_open, num_closed};
    }

    constexpr static std::string to_str(
        const std::string_view& s,
        const Bitset& view)
    {
        std::string r;
        r.reserve(s.size());

        for (uint8_t i = 0; i != s.size(); ++i)
        {
            if (view[i]) r.push_back(s[i]);
        }

        return r;
    }

    constexpr static void impl(
        const std::string_view& str,
        const Bitset& view,
        uint8_t l,
        uint8_t r,
        std::unordered_set<Bitset>& results)
    {
        if (l == 0 && r == 0)
        {
            results.insert(view);
            return;
        }

        std::optional<char> prev_char;

        auto iter = view;

        uint8_t i = 0;

        auto next_idx = [&]
        {
            i = static_cast<uint8_t>(
                std::countr_zero(static_cast<uint32_t>(iter.to_ulong())));
            if (i < str.size())
            {
                iter[i] = false;
                return true;
            }

            return false;
        };

        while (next_idx())
        {
            char c = str[i];
            if (c == prev_char) continue;
            prev_char = c;

            if (!((c == '(' && l) || (c == ')' && r))) continue;

            Bitset alt = view;
            alt[i] = false;

            // Discard if number of orphaned symbols does not improve
            auto [l2, r2] = countOrphans(str, alt);
            if ((l2 < l || r2 < r)) impl(str, alt, l2, r2, results);
        }
    }

    [[nodiscard]] static constexpr std::vector<std::string>
    removeInvalidParentheses(std::string_view s)
    {
        Bitset view = ~Bitset{};
        // Remove leading ')'
        [&]
        {
            for (uint8_t i = 0; i != s.size(); ++i)
            {
                switch (s[i])
                {
                case ')':
                    view[i] = false;
                    break;
                case '(':
                    return;
                }
            }
        }();

        // Remove final '('
        [&]
        {
            if (s.empty()) return;

            uint8_t i = static_cast<uint8_t>(s.size());
            do
            {
                switch (s[--i])
                {
                case '(':
                    view[i] = false;
                    break;
                case ')':
                    return;
                }

            } while (i != 0);
        }();

        std::unordered_set<Bitset> views;
        auto [l, r] = countOrphans(s, view);
        impl(s, view, l, r, views);

        return std::ranges::to<std::vector>(
            views | std::views::transform([&](const Bitset& view)
                                          { return to_str(s, view); }));
    }
};
