#include <cmath>

#include "cast.hpp"

class Solution
{
public:
    int countTriples(int n)
    {
        int count = 0, n2 = n * n;

        for (int a = 1; a <= n; a++)
        {
            for (int b = a + 1; b <= n; b++)
            {
                int c2 = a * a + b * b;
                if (c2 > n2) break;

                int c = cast<int>(std::sqrt(cast<float>(c2)));

                if (c <= n && c * c == c2)
                {
                    count++;
                }
            }
        }
        return count * 2;
    }
};
