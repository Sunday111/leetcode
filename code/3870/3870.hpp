#include <algorithm>
class Solution
{
public:
    static int countCommas(int n) { return std::max(n - 999, 0); }
};
