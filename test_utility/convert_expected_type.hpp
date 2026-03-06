#pragma once

#include <type_traits>
template <typename T, typename Enabled = void>
struct ConvertExpectedType
{
    using Result = T;
};

template <typename T>
using convert_expected_type_t =
    std::remove_reference_t<typename ConvertExpectedType<T>::Result>;
