#pragma once

#include <functional>

#include "max2.hpp"
#include "upd.hpp"

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);
