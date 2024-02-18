//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#ifndef SEARCH_HPP
#define SEARCH_HPP

namespace CTL {

template <typename T>
int linear_search(const T arr[], int size, T key);

template <typename T>
int binary_search(const T arr[], int size, T key);

}  // namespace CTL

#include "../../src/algorithms/search.cpp"

#endif  // SEARCH_HPP