#include <algorithm>
#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    auto maxTotalValue(const std::vector<int>& nums, u32 k) noexcept
    {
        auto [lo, hi] = std::ranges::minmax(nums);
        return static_cast<u64>(hi - lo) * k;
    }
};
