#include <string>
#include <vector>

#include "cast.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    int closestTarget(std::vector<std::string>& w, std::string& t, int s)
        const noexcept
    {
        int n = cast<int>(w.size()), r = n;
        auto d = w.data();
        auto u = std::bind(upd_min, std::ref(r), std::placeholders::_1);
        for (int i = 0; i != n; ++i)
        {
            if (d[i] == t)
            {
                int k = i - s;
                u(std::abs(k));
                u(std::abs(n - k));
                u(std::abs(n + k));
            }
        }
        return r == n ? -1 : r;
    }
};
