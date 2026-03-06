#pragma once

template <typename T, typename Enabled = void>
struct ConvertExpectedType
{
    using Result = T;
};

template <typename T>
using convert_expected_type_t = typename ConvertExpectedType<T>::Result;
