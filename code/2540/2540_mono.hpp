#include <algorithm>
#include <vector>


class Solution
{
public:
    int getCommon(const std::vector<int>& a0, const std::vector<int>& a1)
    {
        using It = decltype(begin(a0));
        It b[2]{begin(a0), begin(a1)};
        It e[2]{end(a0), end(a1)};
        while (b[0] != e[0] && b[1] != e[1])
        {
            if (*b[0] == *b[1]) return *b[0];
            bool u = *b[0] > *b[1];
            b[u] = std::lower_bound(b[u], e[u], *b[!u]);
        }
        return -1;
    }
};
