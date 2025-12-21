#include <algorithm>
#include <bitset>
#include <optional>
#include <span>
#include <string>

using u8 = uint8_t;
using u64 = uint64_t;

class Solution
{
public:
    std::span<const std::string> strs;
    u8 dfs(u8 x, u8 prev_sorted, std::bitset<128> exclude_row)
    {
        if (x == strs.front().size())
        {
            return 0;
        }

        u8 result = strs[0].size() & 0xFF;

        struct Group
        {
            u8 first_row = 0;
            u8 size = 0;
            char c = 0;
        };

        bool sorted = true;
        u8 max_group = 1;

        auto sorted_exclude = exclude_row;
        auto close_group = [&](std::optional<Group> group)
        {
            if (group)
            {
                max_group = std::max(group->size, max_group);
                if (group->size == 1) sorted_exclude[group->first_row] = 1;
            }
        };

        if (prev_sorted == 0xFF)
        {
            std::optional<Group> g;

            for (u8 row = 0; row != strs.size(); ++row)
            {
                if (exclude_row[row])
                {
                    close_group(g);
                    continue;
                }

                char c = strs[row][x];

                if (!g)
                {
                    g = Group{.first_row = row, .size = 1, .c = c};
                    continue;
                }

                if (c < g->c)
                {
                    sorted = false;
                    break;
                }

                if (c == g->c)
                {
                    g->size++;
                }
                else
                {
                    close_group(g);
                    g = Group{
                        .first_row = row,
                        .size = 1,
                        .c = c,
                    };
                }
            }

            close_group(g);
        }
        else
        {
            std::optional<Group> outer;
            std::optional<Group> inner;

            for (u8 row = 0; row != strs.size(); ++row)
            {
                if (exclude_row[row])
                {
                    close_group(inner);
                    outer = inner = std::nullopt;
                    continue;
                }

                char outer_char = strs[row][prev_sorted & 0xFF];
                char inner_char = strs[row][x];

                if (!outer)
                {
                    outer = Group{
                        .first_row = row,
                        .size = 1,
                        .c = outer_char,
                    };
                    inner = Group{
                        .first_row = row,
                        .size = 1,
                        .c = inner_char,
                    };
                    continue;
                }

                if (outer_char != outer->c)
                {
                    close_group(inner);
                    outer = Group{
                        .first_row = row,
                        .size = 1,
                        .c = outer_char,
                    };
                    inner = Group{
                        .first_row = row,
                        .size = 1,
                        .c = inner_char,
                    };
                    continue;
                }

                if (inner_char < inner->c)
                {
                    sorted = false;
                    break;
                }

                if (inner_char != inner->c)
                {
                    close_group(inner);
                    inner = Group{
                        .first_row = row,
                        .size = 1,
                        .c = inner_char,
                    };
                    continue;
                }

                inner->size++;
            }

            close_group(inner);
        }

        if (sorted)
        {
            if (max_group == 1)
            {
                result = 0;
            }
            else
            {
                result = std::min(dfs(x + 1, x, sorted_exclude), result);
            }
        }

        if (result != 0)
        {
            u8 alt = dfs(x + 1, prev_sorted, exclude_row) + 1;
            result = std::min(alt, result);
        }

        return result;
    }

    u8 minDeletionSize(std::span<const std::string> strs_)
    {
        strs = strs_;
        return dfs(0, 0xFF, {});
    }
};
