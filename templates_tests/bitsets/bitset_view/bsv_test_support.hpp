#pragma once

#include <gtest/gtest.h>

#include <array>
#include <cstdint>

template <typename Word, typename Check>
constexpr bool bsv_check_extents(Check check)
{
    constexpr auto width = sizeof(Word) * 8;
    return check.template operator()<Word, 0>() &&
           check.template operator()<Word, 1>() &&
           check.template operator()<Word, width - 1>() &&
           check.template operator()<Word, width>() &&
           check.template operator()<Word, 2 * width + 1>();
}

template <typename Check>
constexpr bool bsv_check_words(Check check)
{
    return bsv_check_extents<std::uint8_t>(check) &&
           bsv_check_extents<std::uint16_t>(check) &&
           bsv_check_extents<std::uint32_t>(check) &&
           bsv_check_extents<std::uint64_t>(check);
}
