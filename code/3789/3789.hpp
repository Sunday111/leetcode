#include <algorithm>
#include <cstdint>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;
    u64 minimumCost(u32 c1, u32 c2, u32 c12, u32 n1, u32 n2)
    {
        u32 t = std::min(n1, n2);
        return u64{std::min(c12, c1 + c2)} * t +
               u64{std::min(c12, c1)} * (n1 - t) +
               u64{std::min(c12, c2)} * (n2 - t);
    }
};
