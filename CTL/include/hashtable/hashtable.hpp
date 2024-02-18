//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 18, 2024.
//

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cmath>
#include <list>
#include <utility>
#include <vector>

namespace CTL {

template <typename K, typename V>
class HashTable {
   private:
    int hash_groups;
    int elements;
    std::vector<std::list<std::pair<K, V>>> table;

    int horner_hash(const K& key, int base = 31,
                    int mod = static_cast<int>(std::pow(10, 9)) + 9) const;
    void resize();

   public:
    explicit HashTable(int hash_groups = 10);
    std::pair<K, V> insert(const K& key, const V& value);
    void remove(const K& key);
    V get(const K& key) const;
    int empty() const;
    std::vector<std::list<std::pair<K, V>>> get_table() const;
};

}  // namespace CTL

#include "../../src/hashtable/hashtable.cpp"

#endif  // HASHTABLE_HPP