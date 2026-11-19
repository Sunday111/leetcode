#include <string>

class Solution
{
public:
    long numSub(const std::string& s)
    {
        long r = 0;
        int o = 0;
        constexpr int kMOD = 1'000'000'007;
        for (char c : s)
        {
            c -= '0';
            if (!c)
            {
                r += ((long{o} * long{o + 1}) / 2);
                o = 0;
            }
            o += c;
        }
        r += ((long{o} * long{o + 1}) / 2);
        r %= kMOD;
        return r;
    }
};
