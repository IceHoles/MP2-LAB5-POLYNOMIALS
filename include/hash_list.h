#pragma once
#include <vector>
#include "list.h"
#include <stdexcept>
//
//uint32_t MurmurHash3(const void* key, size_t len, uint32_t seed = 0) {
//    const uint8_t* data = static_cast<const uint8_t*>(key);
//    const int nblocks = len / 4;
//
//    uint32_t h1 = seed;
//
//    const uint32_t c1 = 0xcc9e2d51;
//    const uint32_t c2 = 0x1b873593;
//
//    // Body
//    const uint32_t* blocks = reinterpret_cast<const uint32_t*>(data);
//    for (int i = 0; i < nblocks; i++) {
//        uint32_t k1 = blocks[i];
//        k1 *= c1;
//        k1 = (k1 << 15) | (k1 >> 17);
//        k1 *= c2;
//
//        h1 ^= k1;
//        h1 = (h1 << 13) | (h1 >> 19);
//        h1 = h1 * 5 + 0xe6546b64;
//    }
//
//    // Tail
//    const uint8_t* tail = static_cast<const uint8_t*>(data) + nblocks * 4;
//    uint32_t k1 = 0;
//    switch (len & 3) {
//    case 3:
//        k1 ^= tail[2] << 16;
//    case 2:
//        k1 ^= tail[1] << 8;
//    case 1:
//        k1 ^= tail[0];
//        k1 *= c1;
//        k1 = (k1 << 15) | (k1 >> 17);
//        k1 *= c2;
//        h1 ^= k1;
//    };
//
//    // Finalization
//    h1 ^= len;
//    h1 ^= h1 >> 16;
//    h1 *= 0x85ebca6b;
//    h1 ^= h1 >> 13;
//    h1 *= 0xc2b2ae35;
//    h1 ^= h1 >> 16;
//
//    return h1;
//}
//
//template <typename TKey, typename TValue>
//class THashTab1e {
//    struct HashNode {
//        TKey key;
//        TValue value;
//    };
//    std::vector<List<HashNode>> table;
//};

// Вспомогательная функция для вычисления хеш-кода с помощью MurmurHash
template <typename TKey>
size_t MurmurHash(const TKey& key) {
    // Реализация MurmurHash может быть разной в зависимости от типа ключа
    // Здесь представлена простая реализация для строковых ключей
    const uint64_t m = 0xc6a4a7935bd1e995;
    const uint64_t r = 47;
    const size_t len = sizeof(TKey);
    const uint8_t* data = (const uint8_t*)&key;
    const uint64_t seed = 0;
    uint64_t h = seed ^ (len * m);
    while (len >= 8) {
        uint64_t k;
        memcpy(&k, data, sizeof(uint64_t));
        data += sizeof(uint64_t);
        len -= sizeof(uint64_t);
        k *= m;
        k ^= k >> r;
        k *= m;
        h ^= k;
        h *= m;
    }
    switch (len) {
    case 7: h ^= uint64_t(data[6]) << 48;
    case 6: h ^= uint64_t(data[5]) << 40;
    case 5: h ^= uint64_t(data[4]) << 32;
    case 4: h ^= uint64_t(data[3]) << 24;
    case 3: h ^= uint64_t(data[2]) << 16;
    case 2: h ^= uint64_t(data[1]) << 8;
    case 1: h ^= uint64_t(data[0]);
        h *= m;
    };
    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    return (size_t)h;
}

template <typename TKey, typename TValue>
class THashTab1e {
    struct HashNode {
        TKey key;
        TValue value;
        //HashNode(const TKey& k, const TValue& v) : key(k), value(v) {}
    };
    size_t size;
    size_t capacity;
    std::vector<List<HashNode>> table;

    // Вспомогательная функция для перехеширования таблицы при переполнении
    void rehash(size_t newCapacity) {
        std::vector<List<HashNode>> newTable(newCapacity);
        for (auto& chain : table) {
            for (auto& node : chain) {
                size_t newIndex = MurmurHash(node.key) % newCapacity;
                newTable[newIndex].push_back(node);
            }
        }
        capacity = newCapacity;
        std::swap(table, newTable);
    }

public:
    THashTab1e() : size(0), capacity(16) {
        table.resize(capacity);
    }
    THashTab1e(size_t initialCapacity) : size(0), capacity(initialCapacity) {
        table.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (size >= capacity * 0.75) rehash(capacity * 2);
        size_t index = MurmurHash(key) % capacity;
        auto& chain = table[index];
        for (auto& node : chain) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        chain.push_back(HashNode(key, value));
        ++size;
    }

    void erase(const TKey& key) {
        size_t index = MurmurHash(key) % capacity;
        auto& chain = table[index];
        for (auto it : chain) {
            if (it->key == key) {
                chain.erase(it);
                --size;
                return;
            }
        }
    }

    TValue& operator[](const TKey& key) {
        size_t index = MurmurHash(key) % capacity;
        for (auto& node : table[index]) {
            if (node.key == key) {
                return node.value;
            }
        }
        throw std::runtime_error("Key not found in hash table");
    }

    const TValue& operator[](const TKey& key) const {
        size_t index = MurmurHash(key) % capacity;
        for (auto& node : table[index]) {
            if (node.key == key) {
                return node.value;
            }
        }
        throw std::runtime_error("Key not found in hash table");
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};