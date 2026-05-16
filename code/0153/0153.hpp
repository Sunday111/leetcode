#include <vector>

class Solution
{
public:
    int findMin(const std::vector<int>& a)
    {
        auto d = a.data();
        int i[]{0, static_cast<int>(a.size() - 1)};
        while (i[0] < i[1])
        {
            int m = (i[0] + i[1]) / 2;
            bool b = d[m] > d[i[1]];
            i[!b] = m + b;
        }
        return d[i[0]];
    }
};
