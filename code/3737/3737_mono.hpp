#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] constexpr auto countMajoritySubarrays(
        std::vector<int>& nums,
        int target) noexcept
    {
        const u16 n = nums.size() & 0xFFFF, n1 = n + 1;

        u16 f[1001];
        for (u16 i = 1, t = 0; int x : nums)
        {
            t += x == target;
            f[i++] = t;
        }

        u32 r = 0;
        for (u16 i = 0; f[i] != f[n]; ++i)
        {
            for (u16 l = 1, j = i + 1; j != n1; ++j, ++l)
            {
                r += l / 2 < (f[j] - f[i]);
            }
        }

        return r;
    }
};
