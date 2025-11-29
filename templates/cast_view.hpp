#pragma once

#include <ranges>

#include "cast.hpp"

template <typename To>
inline static constexpr auto cast_view = std::views::transform(cast<To>);
