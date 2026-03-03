#include <string>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    struct Cnt
    {
        void add(char c) noexcept
        {
            u8 i = (c - 'a') & 31;
            bits |= (1u << i);
            ++freq[i];
            ++size;
        }

        void remove(char c) noexcept
        {
            u8 i = (c - 'a') & 31;
            --freq[i];
            bits &= ~(u32{!freq[i]} << i);
            --size;
        }

        u32 bits = 0;
        u16 freq[26]{};
        u16 size = 0;
    };

    auto partitionLabels(const std::string& s)
    {
        Cnt left{}, right{};

        for (char c : s) right.add(c);

        std::vector<int> r;
        for (char c : s)
        {
            right.remove(c);
            left.add(c);
            if (left.bits & right.bits) continue;
            r.emplace_back(left.size);
            left = {};
        }

        return r;
    }
};
