#include <cstdint>
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
    [[nodiscard]] static constexpr u32 minimumPrefixLength(
        const std::vector<int>& nums) noexcept
    {
        u32 i = static_cast<u32>(nums.size() - 1);
        while (i-- && nums[i] < nums[i + 1]);
        return i - 0xFFFFFFFF;
    }
};
