//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 18, 2024.
//

#include "../../include/hashtable/hashtable.hpp"

#include <string>

namespace CTL {

template <typename K, typename V>
int HashTable<K, V>::horner_hash(const K& key, int base, int mod) const {
    int hash = 0;

    for (auto c : key) {
        hash = (hash * base + c) % mod;
    }

    return hash;
}

template <typename K, typename V>
void HashTable<K, V>::resize() {
    if (elements / hash_groups < 3) return;

    int new_hash_groups = hash_groups * 2;
    std::vector<std::list<std::pair<K, V>>> new_table(new_hash_groups);

    for (auto& group : table) {
        for (auto& element : group) {
            int new_group = horner_hash(element.first, 31, new_hash_groups);
            new_table[new_group].push_back(element);
        }
    }

    table = new_table;
    hash_groups = new_hash_groups;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(int hash_groups)
    : hash_groups(hash_groups), elements(0), table(hash_groups) {}

template <typename K, typename V>
std::pair<K, V> HashTable<K, V>::insert(const K& key, const V& value) {
    int group = horner_hash(key, 31, hash_groups);
    auto& bucket = table[group];

    std::pair<K, V> ret = {key, value};

    // Check for existing key and update.
    for (auto& pair : bucket) {
        if (pair.first == key) {
            pair.second = value;
            return ret;
        }
    }

    // Otherwise, add the new key-value pair.
    bucket.push_back({key, value});
    elements++;

    resize();

    return ret;
}

template <typename K, typename V>
void HashTable<K, V>::remove(const K& key) {
    int group = horner_hash(key, 31, hash_groups);
    auto& bucket = table[group];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            elements--;
            break;
        }
    }
}

template <typename K, typename V>
V HashTable<K, V>::get(const K& key) const {
    int group = horner_hash(key, 31, hash_groups);
    const auto& bucket = table[group];

    for (const auto& pair : bucket) {
        if (pair.first == key) {
            return pair.second;
        }
    }

    // If the key is not found, return an empty value.
    return V();
}

template <typename K, typename V>
int HashTable<K, V>::empty() const {
    return elements == 0;
}

template <typename K, typename V>
std::vector<std::list<std::pair<K, V>>> HashTable<K, V>::get_table() const {
    return table;
}

}  // namespace CTL