#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#include <algorithm>
#include <cassert>
#include <vector>

using u32 = uint32_t;
std::pair<int, int> pu[100'001];  // NOLINT
std::pair<int, u32> pt[100'001];  // NOLINT

class TaskManager
{
public:
    explicit TaskManager(std::vector<std::vector<int>>& tasks) noexcept
    {
        for (auto& t : tasks)
        {
            int userId = t[0], priority = t[2];
            u32 taskId = static_cast<u32>(t[1]);
            max_t = std::max(max_t, taskId);
            pu[taskId] = {priority, userId};
            pt[pqs++] = {priority, taskId};
        }

        std::make_heap(pt, pt + pqs);  // NOLINT
    }

    ~TaskManager() noexcept
    {
        std::ranges::fill_n(pu, max_t + 1, std::make_pair(-1, -1));
    }

    void add(int userId, u32 taskId, int priority) noexcept
    {
        pu[taskId] = {priority, userId};
        pt[pqs++] = {priority, taskId};
        std::push_heap(pt, pt + pqs);  // NOLINT
    }

    void edit(u32 taskId, int newPriority) noexcept
    {
        pu[taskId].first = newPriority;
        pt[pqs++] = {newPriority, taskId};
        std::push_heap(pt, pt + pqs);  // NOLINT
    }

    void rmv(u32 taskId) noexcept { pu[taskId].first = -1; }

    int execTop() noexcept
    {
        while (pqs)
        {
            auto [priority, task] = *pt;
            std::pop_heap(pt, pt + pqs--);  // NOLINT
            if (pu[task].first == priority)
            {
                int user = pu[task].second;
                pu[task] = {-1, -1};
                return user;
            }
        }
        return -1;
    }

private:
    u32 max_t = 0, pqs = 0;
};
