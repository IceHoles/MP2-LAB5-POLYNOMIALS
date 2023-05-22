#pragma once
#include <vector>
#include "list.h"
#include <stdexcept>

template <typename TKey>
size_t MurmurHash(const TKey& key) {
    const uint64_t m = 0xc6a4a7935bd1e995;
    const uint64_t r = 47;
    const size_t length = sizeof(TKey);
    const uint8_t* data = (const uint8_t*)&key;
    const uint64_t seed = 0;
    size_t len = length;
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
        HashNode() = default;
        HashNode(const TKey& k, const TValue& v) : key(k), value(v) {};
    };
    size_t size;
    size_t capacity;
    std::vector<List<HashNode>> table;

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
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if ((*it).key == key) {
                chain.erase(it.get_node());
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

    void print() {
        std::cout << "hash table contains :" << std::endl;
        for (auto node : table) {
            for (auto it : node) {
                std::cout << it.key << " = " << it.value << std::endl;
            }
        }
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};