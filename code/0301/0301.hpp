#include <bit>
#include <cassert>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    std::vector<std::string> results;

    [[nodiscard]] static std::tuple<u8, u8> countOrphans(
        const std::string& s,
        u32 view)
    {
        u8 num_open = 0;
        u8 num_closed = 0;

        u8 i = 0;

        auto next_idx = [&]
        {
            i = std::countr_zero(view) & 0xFF;
            if (i < s.size())
            {
                view &= ~(u32{1} << i);
                return true;
            }

            return false;
        };

        while (next_idx())
        {
            bool b = s[i] == '(';
            num_open += b;
            switch (s[i])
            {
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

    constexpr static std::string to_str(const std::string& s, u32 view)
    {
        std::string r;
        r.reserve(s.size());

        for (u8 i = 0; i != s.size(); ++i)
        {
            if (view & (u32{1} << i)) r.push_back(s[i]);
        }

        return r;
    }

    constexpr void impl(const std::string& str, u32 view, u32 iter, u8 l, u8 r)
    {
        if (l == 0 && r == 0)
        {
            results.push_back(to_str(str, view));
            return;
        }

        char prev_char = 0;

        u8 i = 0;

        auto next_idx = [&]
        {
            i = std::countr_zero(iter) & 0xFF;
            if (i < str.size())
            {
                iter &= ~(u32{1} << i);
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

            u32 alt = view;
            alt &= ~(u32{1} << i);

            // Discard if number of orphaned symbols does not improve
            auto [l2, r2] = countOrphans(str, alt);
            if ((l2 < l || r2 < r))
            {
                impl(str, alt, iter, l2, r2);
            }
        }
    }

    constexpr static void strip_left(const std::string& s, u32& view)
    {
        // Remove leading ')'
        for (u8 i = 0, leading = 1; i != s.size(); ++i)
        {
            leading &= s[i] != '(';
            view &= ~((u32{leading} & (s[i] == ')')) << i);
        }
    }

    constexpr static void strip_right(const std::string& s, u32& view)
    {
        // Remove final '('
        for (u8 i = s.size() & 0xFF, trailing = 1; i != 0;)
        {
            --i;
            trailing &= s[i] != ')';
            view &= ~((u32{trailing} & (s[i] == '(')) << i);
        }
    }

    [[nodiscard]] constexpr std::vector<std::string> removeInvalidParentheses(
        const std::string& s) noexcept
    {
        results.clear();
        u32 view = (u32{1} << s.size()) - 1;
        strip_left(s, view);
        strip_right(s, view);
        auto [l, r] = countOrphans(s, view);
        impl(s, view, view, l, r);
        return std::move(results);
    }
};
