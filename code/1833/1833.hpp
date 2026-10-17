#include <vector>

#include "cast.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

class Solution
{
public:
    inline static u32 freq[100'001];
    inline static PyramidBitset<100'001> b{};

    [[nodiscard]] auto maxIceCream(const std::vector<int>& costs, u32 coins)
        const noexcept
    {
        u32 r = 0;

        // Put items into priority queue of unique
        // elements and record frequencies
        for (int x : costs)
        {
            pbs_add(b, cast<u32>(x));
            freq[x] += 1;
        }

        // Take elements from the queue one by one
        while (!pbs_is_empty(b))
        {
            auto x = pbs_min(b);
            // t: by as many bars with price 'x' as possible and
            // reset frequency value to make 'freq' self-cleaning
            // to prevent zeroing everything every time
            u32 t = std::min(coins / x, std::exchange(freq[x], 0));
            coins -= t * x;
            r += t;
            pbs_remove(b, x);
        }

        return r;
    }
};
