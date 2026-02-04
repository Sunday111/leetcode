#pragma once

// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7
#ifdef LC_LOCAL_BUILD
int rand7()
{
    return 0;
}
#endif

class Solution
{
public:
    int rand10()
    {
        int s = 0;
        for (int i = 0; i != 10; ++i)
        {
            s += rand7();
        }

        return (s % 10) + 1;
    }
};
