#include <algorithm>
#include <unordered_map>

#include "bump_hash_map.hpp"
#include "bump_vector.hpp"

using SolutionStorage = GlobalBufferStorage<1 << 23>;

class Solution
{
public:
    [[nodiscard]] FORCE_INLINE i64 gethash(u32 a, u32 b) noexcept
    {
        const u32 vm = ~(-1u << 17);
        u32 a1 = (a & vm), b1 = (b & vm);
        if (a < 0) a1 |= (1 << 17);
        if (b < 0) b1 |= (1 << 17);
        return ((i64{a1} << 18) | b1);
    }

    u32 longestBalanced(const std::string& s)
    {
        u32 n = static_cast<u32>(s.size());
        u32 ans = 1;
        for (u32 i = 0, cnt = 0; i != n; ++i)
        {
            ++cnt;
            if (i + 1 == n || s[i + 1] != s[i])
            {
                ans = std::max(ans, cnt);
                cnt = 0;
            }
        }

        if (ans == n) return ans;

        {
            const auto arena = SolutionStorage::Instance().StartArena();
            ObjectWithoutDtor<BumpVector<int, SolutionStorage>> dp, dn;
            for (int c = 0; c != 3; ++c)
            {
                int c2 = (c + 1) % 3;
                int d = 0, lb = 0;
                arena.Reset();
                dp.Reset();
                dn.Reset();
                dp->resize(n + 1, -1);
                dn->resize(n + 1, -1);
                dp.get()[0] = 0;
                for (u32 i = 0; i != n; ++i)
                {
                    if (s[i] - 'a' == c)
                    {
                        ++d;
                    }
                    else if (s[i] - 'a' == c2)
                    {
                        --d;
                    }
                    else
                    {
                        d = 0;
                        lb = i + 1;
                    }

                    if (d >= 0)
                    {
                        if (dp.get()[d] >= lb)
                        {
                            ans = std::max(ans, i + 1 - dp.get()[d]);
                        }
                        else
                        {
                            dp.get()[d] = i + 1;
                        }
                    }
                    else
                    {
                        if (dn.get()[-d] >= lb)
                        {
                            ans = std::max(ans, i + 1 - dn.get()[-d]);
                        }
                        else
                        {
                            dn.get()[-d] = i + 1;
                        }
                    }
                }
            }
        }

        const auto arena = SolutionStorage::Instance().StartArena();
        ObjectWithoutDtor<BumpHashMap<u64, u32, SolutionStorage>> mp;
        mp.get()[0] = 0;
        for (u32 i = 0, a = 0, b = 0; i != n; ++i)
        {
            switch (s[i])
            {
            case 'a':
                ++a;
                break;
            case 'b':
                --a;
                ++b;
                break;
            default:
                --b;
                break;
            }
            u64 hs = (u64{a} << 20) | u64{b};
            auto it = mp->try_emplace(hs, i + 1).first;
            ans = std::max(ans, i + 1u - it->second);
        }
        return ans;
    }
};

#include "sync_stdio.hpp"
