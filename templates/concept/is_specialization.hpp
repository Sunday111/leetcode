#pragma once

#include <type_traits>

template <typename Test, template <typename...> typename Type>
struct IsSpecialization : std::false_type
{
};

template <template <typename...> typename Type, typename... Args>
struct IsSpecialization<Type<Args...>, Type> : std::true_type
{
};

template <typename Test, template <typename...> typename Type>
concept is_specialization = IsSpecialization<Test, Type>::value;
