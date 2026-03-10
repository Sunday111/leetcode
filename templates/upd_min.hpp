#pragma once

#include <functional>

#include "min2.hpp"
#include "upd.hpp"

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);
