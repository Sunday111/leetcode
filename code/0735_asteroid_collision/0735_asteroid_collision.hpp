#pragma once

#include <vector>

class Solution
{
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids)
    {
        int last_r = -1;

        for (size_t i = 0; i != asteroids.size(); ++i)
        {
            int& v = asteroids[i];

            auto push = [&]
            {
                asteroids[std::bit_cast<uint32_t>(++last_r)] = v;
            };

            if (v > 0)
            {
                push();
                continue;
            }

            while (true)
            {
                int last = -1;
                if (last_r >= 0)
                {
                    last = asteroids[std::bit_cast<uint32_t>(last_r)];
                }

                if (last < 0)
                {
                    push();
                    break;
                }

                if (last < -v)
                {
                    --last_r;
                    continue;
                }

                if (last > -v)
                {
                    break;
                }

                --last_r;
                break;
            }
        }

        asteroids.resize(static_cast<size_t>(last_r + 1));

        return std::move(asteroids);
    }
};
