#pragma once

#include <atomic>
#include <functional>
#include <semaphore>

class H2O
{
public:
    H2O() = default;

    std::binary_semaphore o{1};
    std::counting_semaphore<2> h{0};
    std::atomic<int> num_h = 0;

    void hydrogen(const std::function<void()>& releaseHydrogen)
    {
        h.acquire();
        releaseHydrogen();
        if (num_h.fetch_add(1, std::memory_order_acq_rel) & 1) o.release();
    }

    void oxygen(const std::function<void()>& releaseOxygen)
    {
        o.acquire();
        releaseOxygen();
        h.release(2);
    }
};
