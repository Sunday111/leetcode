#pragma once

#include <algorithm>
#include <queue>
#include <vector>

class Solution
{
public:
    std::vector<int> deckRevealedIncreasing(std::vector<int>& deck)
    {
        std::ranges::sort(deck);

        const size_t n = deck.size();

        std::queue<size_t> q;
        for (size_t i = 0; i != n; ++i) q.push(i);

        std::vector<int> r;
        r.resize(n);
        size_t i = 0;

        bool yield = true;
        while (!q.empty())
        {
            size_t idx = q.front();
            q.pop();
            if (yield)
            {
                r[idx] = deck[i++];
            }
            else
            {
                q.push(idx);
            }

            yield = !yield;
        }

        return r;
    }
};
