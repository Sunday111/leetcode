#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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
        }

        void remove(char c) noexcept
        {
            u8 i = (c - 'a') & 31;
            --freq[i];
            bits &= ~(u32{!freq[i]} << i);
        }

        [[nodiscard]] u16 size() const noexcept
        {
            return std::ranges::fold_left(freq, u16{}, std::plus<u16>{});
        }

        void clear() noexcept
        {
            bits = 0;
            std::ranges::fill(freq, 0);
        }

        u32 bits = 0;
        u16 freq[26]{};
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
            r.emplace_back(left.size());
            left.clear();
        }

        return r;
    }
};
