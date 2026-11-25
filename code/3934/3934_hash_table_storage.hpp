#pragma once

#include <bit>

#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"

struct HashTableStorage
{
    struct Entry
    {
        u32 key;
        u32 value;
    };
    static constexpr u32 kCapacity = std::bit_ceil(2u * 100'000);
    Entry table[kCapacity];
    u64 bits[kCapacity / 64];
};

template <u32 capacity>
    requires(
        std::has_single_bit(capacity) &&
        capacity <= HashTableStorage::kCapacity)
struct HashTable
{
    HashTableStorage& storage;

    [[nodiscard, gnu::always_inline]] u32 increment(u32 k) noexcept
    {
        u64 z = u64{k} + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        u32 i = static_cast<u32>(z >> 32);
        BitsetView<u64, capacity> used{storage.bits};
        bool present = false;
        do
        {
            i = (i + 1) & (capacity - 1);
            present = bsv_get(used, i);
        } while (present & (storage.table[i].key != k));

        auto& e = storage.table[i];
        e.key = k;
        e.value = iif(present, e.value + 1, 1u);
        bsv_set<true>(used, i);
        return e.value;
    }
};
