#include <algorithm>
#include <span>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] u32 canJump(std::span<const int> nums_) noexcept
    {
        const auto nums = reinterpret_cast<const u32*>(nums_.data());
        const u32 target = static_cast<u32>(nums_.size() - 1);
        u32 curr = 0;
        for (u32 next = 0, i = 0; curr < target && i <= next; ++i)
        {
            next = std::max(next, i + nums[i]);
            bool b = curr == i;
            curr = (next & -u32{b}) | (curr & -u32{!b});
        }
        return curr >= target;
    }
};
