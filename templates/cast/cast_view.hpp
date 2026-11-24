#pragma once

#include <ranges>

#include "cast/cast.hpp"

template <typename To>
inline static constexpr auto cast_view = std::views::transform(cast<To>);
