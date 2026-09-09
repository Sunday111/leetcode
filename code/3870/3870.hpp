#include <algorithm>
class Solution
{
public:
    int countCommas(int n) { return std::max(n - 999, 0); }
};
