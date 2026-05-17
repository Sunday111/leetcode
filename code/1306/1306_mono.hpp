#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    bool canReach(const std::vector<int>& a, u32 start)
    {
        u32 n = static_cast<u32>(a.size());
        std::vector<bool> vis(n + 1, false);
        vis[n] = 1;
        u32 q[20000], qs = 0;
        q[qs++] = start;
        while (qs)
        {
            u32 i = q[--qs];
            if (vis[i]) continue;
            vis[i] = true;
            u32 d = static_cast<u32>(a[i]);
            if (!d) return true;
            u32 l = std::min(i - d, n), r = std::min(i + d, n);
            q[qs] = l;
            qs += !vis[l];
            q[qs] = r;
            qs += !vis[r];
        }
        return false;
    }
};
