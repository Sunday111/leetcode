#pragma once

#include <vector>

class Solution
{
public:
    bool validateStackSequences(
        std::vector<int>& pushed,
        std::vector<int>& popped)
    {
        size_t next_pop = 0;
        size_t next_push = 0;

        for (auto v : pushed)
        {
            pushed[next_push++] = v;
            while (next_push != 0 && pushed[next_push - 1] == popped[next_pop])
            {
                --next_push;
                ++next_pop;
            }
        }

        return next_push == 0;
    }
};
