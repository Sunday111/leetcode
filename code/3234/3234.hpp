#pragma once

#include <string>

class Solution
{
public:
    int numberOfSubstrings(const std::string& s)
    {
        static uint16_t c1[40'001];
        uint16_t t0{}, t1{};
        int r = c1[0] = 0;

        for (char c : s)
        {
            c -= '0';
            t1 += c;
            c1[t0 + 1] = t1;
            t0 += !c;
            r += t1 - c1[t0];
            for (int c0 = t0; c0--;)
            {
                int z = t0 - c0, zsq = z * z;
                if (zsq > t1) break;
                int hi = t1 - c1[c0];
                int lo = t1 - c1[c0 + 1];
                r += std::max(0, hi - std::max(lo, zsq) + 1);
            }
        }
        return r;
    }
};
