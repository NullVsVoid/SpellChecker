//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/algorithms/search.hpp"

#include <cmath>

namespace CTL {

/**
 * Linear search algorithm is a search algorithm that finds the position of a
 * target value within an array. Linear search compares each element of the
 * array to the target value, and returns the index of the target value in the
 * array if found. If the target value is not found in the array, the algorithm
 * returns -1.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * @param arr The array to search
 * @param target The target value to search for
 * @return The index of the target value in the array, or -1 if not found
 */
template <typename T>
int linear_search(const T arr[], int size, T target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return the index of the target value in the array.
        }
    }

    return -1;  // Return -1 if the target value is not found in the array.
}

/**
 * Binary search algorithm is a search algorithm that finds the position of a
 * target value within a sorted array. Binary search compares the target value
 * to the middle element of the array. If they are not equal, the half in which
 * the target cannot lie is eliminated and the search continues on the remaining
 * half, again taking the middle element to compare to the target value, and
 * repeating this until the target value is found. If the search ends with the
 * remaining half being empty, the target is not in the array.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 *
 * @param arr The array to search
 * @param target The target value to search for
 * @return The index of the target value in the array, or -1 if not found
 */
template <typename T>
int binary_search(const T arr[], int size, T target) {
    int count = 0;  // The running count of number of splits done in the array.
    int left = 0;   // The left index of the array.
    int right = size - 1;  // The right index of the array.

    int index = 0;  // The index of the target value in the array.

    while (left <= right) {
        count++;  // Increment the count of splits done in the array.

        index = std::floor((left + right) /
                           2);  // Calculate the middle index of the array.

        if (arr[index] == target) {
            return index;  // Return the index of the target value in the array.
        } else if (arr[index] < target) {
            left = index + 1;  // Update the left index of the array.
        } else {
            right = index - 1;  // Update the right index of the array.
        }
    }

    return -1;  // Return -1 if the target value is not found in the array.
}

}  // namespace CTL