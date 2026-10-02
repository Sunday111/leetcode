#include "catalan_64.hpp"

static_assert(kCatalan64.front() == 1);
static_assert(kCatalan64.at(8) == 1430);
static_assert(kCatalan64.back() == 11959798385860453492ULL);

static_assert(
    []
    {
        for (u32 n = 1; n < kCatalan64.size(); ++n)
        {
            u64 expected = 0;
            for (u32 i = 0; i < n; ++i)
            {
                expected += kCatalan64.at(i) * kCatalan64.at(n - 1 - i);
            }
            if (kCatalan64.at(n) != expected) return false;
        }
        return true;
    }());
