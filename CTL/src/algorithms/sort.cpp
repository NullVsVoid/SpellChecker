//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/algorithms/sort.hpp"

namespace CTL {

template <typename T>
void insertionSort(T arr[], int size) {
    for (int i = 1; i < size; i++) {
        T current = arr[i];

        int j = i - 1;
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = current;
    }
}

template <typename T>
void selectionSort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            T temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

template <typename T>
void merge(T arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    T left_subarray[n1];
    T right_subarray[n2];

    for (int i = 0; i < n1; i++) {
        left_subarray[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_subarray[i] = arr[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_subarray[i] <= right_subarray[j]) {
            arr[k] = left_subarray[i];
            i++;
        } else {
            arr[k] = right_subarray[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = left_subarray[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_subarray[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(T arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;

            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    T temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

}  // namespace CTL