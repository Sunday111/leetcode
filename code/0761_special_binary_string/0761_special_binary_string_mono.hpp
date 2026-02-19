#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    std::string makeLargestSpecial(std::string& full)
    {
        struct Group
        {
            u8 begin;
            u8 end;
        };

        std::vector<Group> groups;

        u8 n = full.size() & 0xFF;

        {
            u8 f[2]{0, 0};
            for (u8 i = 0; i != n; ++i)
            {
                u8 t = (full[i] - '0') & 1;
                if (t)
                {
                    if (f[1] != 0 && f[0] != 0)
                    {
                        u8 l = std::min(f[0], f[1]);
                        u8 begin = i - (f[0] + l);
                        groups.emplace_back(begin, i - f[0] + l);
                        f[0] = f[1] = 0;
                    }
                    else if (f[1] == 0 && f[0] != 0)
                    {
                        f[0] = 0;
                    }
                }

                ++f[t];
            }

            u8 l = std::min(f[0], f[1]);
            u8 begin = n - (f[0] + l);
            groups.emplace_back(begin, n - f[0] + l);
        }

        auto get_view = [&](Group g)
        {
            return std::string_view{full}.substr(g.begin, g.end - g.begin);
        };

        auto merge = [&](u8 begin, u8 end) -> Group
        {
            if (begin + 1 == end) return groups[begin];

            u8 sbegin = groups[begin].begin;
            u8 send = groups[end - 1].end;
            std::ranges::sort(
                groups.begin() + begin,
                groups.begin() + end,
                std::greater{},
                get_view);

            char buf[51];

            char* out = buf;
            for (u8 i = begin; i != end; ++i)
            {
                auto& g = groups[i];
                out = std::ranges::copy(get_view(g), out).out;
            }

            std::copy_n(buf, send - sbegin, full.data() + sbegin);
            return {sbegin, send};
        };

        auto can_grow_left = [&](u8 gi)
        {
            u8 x = groups[gi].begin - 1;
            return x != 0xFF && full[x] == '1' &&
                   (gi == 0 || x >= groups[gi - 1].end);
        };

        auto can_grow_right = [&](u8 gi, u8 next)
        {
            u8 x = groups[gi].end;
            return x != n && full[x] == '0' &&
                   (next == groups.size() || x < groups[next].begin);
        };

        bool grown = true;
        while (grown)
        {
            grown = false;

            u8 new_num = 0;
            for (u8 i = 0, ng = groups.size() & 0xFF; i != ng;)
            {
                u8 j = i + 1;
                while (j != ng && groups[j].begin == groups[j - 1].end) ++j;

                if (can_grow_left(i) && can_grow_right(j - 1, j))
                {
                    groups[new_num] = merge(i, j);
                    while (can_grow_left(new_num) && can_grow_right(new_num, j))
                    {
                        auto& [b, e] = groups[new_num];
                        --b, ++e;
                    }
                    new_num++;
                    grown = true;
                    i = j;
                }
                else
                {
                    while (i != j)
                    {
                        groups[new_num++] = groups[i++];
                    }
                }
            }
            groups.resize(new_num);
        }

        merge(0, groups.size() & 0xFF);

        return std::move(full);
    }
};
