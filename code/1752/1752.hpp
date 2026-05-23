#include <vector>

class Solution
{
public:
    bool check(std::vector<int>& a, int x = 0)
    {
        for (int p = a.back(); int v : a) x += v < std::exchange(p, v);
        return x < 2;
    }
};
