#include <vector>

#include "pyramid_bitset.hpp"

class Solution
{
public:
    inline static u32 freq[100'001];
    inline static PyramidBitset<100'001> b{kEmpty};

    [[nodiscard]] auto maxIceCream(const std::vector<int>& costs, u32 coins)
        const noexcept
    {
        u32 r = 0;

        // Put items into priority queue of unique
        // elements and record frequencies
        for (int x : costs)
        {
            b.add(cast<u32>(x));
            freq[x] += 1;
        }

        // Take elements from the queue one by one
        for (auto x = b.min(); x < b.get_capacity(); x = b.min())
        {
            // t: by as many bars with price 'x' as possible and
            // reset frequency value to make 'freq' self-cleaning
            // to prevent zeroing everything every time
            u32 t = std::min(coins / x, std::exchange(freq[x], 0));
            coins -= t * x;
            r += t;
            b.remove(x);
        }

        return r;
    }
};
