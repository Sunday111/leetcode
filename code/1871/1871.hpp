#include <algorithm>
#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    bool canReach(const std::string& s, u32 lo, u32 hi) noexcept
    {
        u32 n = static_cast<u32>(s.size()), ni = 0, li = 0;
        if (s.back() == '1') return false;  // last is unreachable
        if (++hi == n) return true;         // one jump is enough

        // rng[i] = reachable range [begin, end)
        static std::pair<u32, u32> rng[100'001];
        rng[ni++] = {std::min(lo, n), hi};

        for (u32 i = 0; (i != ni) & (rng[li].second != n);)
        {
            auto& [j, j_end] = rng[i];
            // range [l, r) reachable from j
            // but not yet queued
            u32 l = std::clamp(j + lo, rng[li].second, n);
            u32 r = std::clamp(j + hi, l, n);
            rng[ni] = {l, r};
            bool ok = (s[j] == '0') & (l != r);
            ni += ok;
            li += ok;
            i += ++j == j_end;
        }
        return rng[li].second == n;
    }
};
