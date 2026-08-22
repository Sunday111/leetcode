class Solution
{
public:
    bool checkDivisibility(int n)
    {
        int s{}, p = {1}, t = n;
        while (t)
        {
            int d = t % 10;
            s += d, p *= d;
            t /= 10;
        }
        return (n % (s + p)) == 0;
    }
};
