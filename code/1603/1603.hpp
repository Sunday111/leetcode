#pragma once

#include <array>

class ParkingSystem
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;

    constexpr ParkingSystem(u16 big, u16 medium, u16 small)
        : capacities{big, medium, small}
    {
    }

    constexpr bool addCar(u8 carType)
    {
        const u8 idx = carType - 1;
        auto& size = sizes[idx];
        if (size == capacities[idx]) return false;
        ++size;
        return true;
    }

    std::array<u16, 3> capacities;
    std::array<u16, 3> sizes{};
};
