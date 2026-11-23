#pragma once

#include <concepts>
#include <type_traits>

template <typename Word>
concept BitsetWord = std::unsigned_integral<Word> &&
                     !std::same_as<std::remove_cv_t<Word>, bool> &&
                     std::same_as<Word, std::make_unsigned_t<Word>>;
