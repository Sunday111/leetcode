#include <array>
#include <cassert>
#include <vector>

#include "bump_set.hpp"

class TaskManager
{
public:
    using UP = std::pair<int, int>;
    using PT = std::pair<int, u32>;
    using SetStorage = GlobalBufferStorage<1 << 25>;
    inline static std::array<UP, 100001> t_up;
    ObjectWithoutDtor<BumpSet<PT, SetStorage, std::greater<PT>>> pt;  // NOLINT

    explicit TaskManager(std::vector<std::vector<int>>& tasks) noexcept
    {
        for (auto& utp : tasks)
        {
            add(utp[0], static_cast<u32>(utp[1]), utp[2]);
        }
    }

    void add(int userId, u32 taskId, int priority) noexcept NO_SANITIZERS
    {
        t_up[taskId] = {userId, priority};
        pt->emplace(priority, taskId);
    }

    void edit(u32 taskId, int newPriority) noexcept NO_SANITIZERS
    {
        auto& [user, priority] = t_up[taskId];
        auto h = pt->extract({priority, taskId});
        priority = h.value().first = newPriority;
        pt->insert(std::move(h));
    }

    void rmv(u32 taskId) noexcept NO_SANITIZERS
    {
        auto& [userId, priority] = t_up[taskId];
        pt->erase({priority, taskId});
    }

    int execTop() noexcept NO_SANITIZERS
    {
        if (pt->empty()) return -1;
        auto pt_it = pt->begin();
        auto& [userId, priority] = t_up[pt_it->second];
        pt->erase(pt_it);
        return userId;
    }
};

#include "sync_stdio.hpp"
