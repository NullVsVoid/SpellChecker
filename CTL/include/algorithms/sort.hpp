//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#ifndef SORT_HPP
#define SORT_HPP

namespace CTL {

template <typename T>
void insertionSort(T arr[], int size);

template <typename T>
void selectionSort(T arr[], int size);

template <typename T>
void mergeSort(T arr[], int left, int right);

template <typename T>
void quickSort(T arr[], int low, int high);

}  // namespace CTL

#include "../../src/algorithms/sort.cpp"

#endif  // SORT_HPP