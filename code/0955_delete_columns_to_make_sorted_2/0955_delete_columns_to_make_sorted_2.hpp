#include <algorithm>
#include <bitset>
#include <span>
#include <string>

using u8 = uint8_t;

class Solution
{
public:
    static constexpr u8 minDeletionSize(
        std::span<const std::string> strs) noexcept
    {
        const u8 w = strs[0].size() & 0xFF;
        u8 last_sorted = w, result = 0;
        std::bitset<128> sorted_rows{};

        for (u8 x = 0; x != w; ++x)
        {
            struct Group
            {
                u8 first_row = 0;
                u8 size = 0;
                char c = 0;
            };

            bool sorted = true;
            u8 max_group = 1;

            auto new_sorted_rows = sorted_rows;

            Group outer, inner;
            auto close_group = [&]
            {
                if (inner.size)
                {
                    max_group = std::max(inner.size, max_group);
                    new_sorted_rows[inner.first_row] = inner.size == 1;
                }
            };

            for (u8 y = 0; y != strs.size() && sorted; ++y)
            {
                if (sorted_rows[y])
                {
                    close_group();
                    outer.size = inner.size = 0;
                    continue;
                }

                const char outer_char = strs[y][last_sorted];
                const char inner_char = strs[y][x];

                if (!outer.size)
                {
                    outer = Group{
                        .first_row = y,
                        .size = 1,
                        .c = outer_char,
                    };
                    inner = Group{
                        .first_row = y,
                        .size = 1,
                        .c = inner_char,
                    };
                    continue;
                }

                if (outer_char != outer.c)
                {
                    close_group();
                    outer = Group{
                        .first_row = y,
                        .size = 1,
                        .c = outer_char,
                    };
                    inner = Group{
                        .first_row = y,
                        .size = 1,
                        .c = inner_char,
                    };
                    continue;
                }

                sorted = inner_char >= inner.c;

                if (inner_char == inner.c)
                {
                    inner.size++;
                }
                else
                {
                    close_group();
                    inner = Group{
                        .first_row = y,
                        .size = 1,
                        .c = inner_char,
                    };
                }
            }

            close_group();

            if (sorted)
            {
                if (max_group < 2) break;

                last_sorted = x;
                sorted_rows = new_sorted_rows;
            }

            result += !sorted;
        }

        return result;
    }
};
