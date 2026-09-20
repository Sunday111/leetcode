class Solution
{
public:
    auto countCommas(unsigned long n)
    {
        auto r = 0ul, t = 1000ul;
        n += 1;
        while (n > t)
        {
            r += n - t;
            t *= 1000ul;
        }

        return r;
    }
};
