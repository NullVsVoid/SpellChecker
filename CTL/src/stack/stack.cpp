//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/stack/stack.hpp"

namespace CTL {

template <typename T>
Stack<T>::Stack(int size) : size(size), currentElem(0) {
    stack = new T[size];
}

template <typename T>
Stack<T>::~Stack() {
    delete[] stack;
}

template <typename T>
void Stack<T>::push(T data) {
    if (isFull()) return;

    if (!isFull()) {
        stack[currentElem++] = data;
    }
}

template <typename T>
T Stack<T>::pop() {
    if (!isEmpty()) {
        return stack[--currentElem];
    }

    return T();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return currentElem == 0;
}

template <typename T>
bool Stack<T>::isFull() const {
    return currentElem == size;
}

template <typename T>
T Stack<T>::peek() const {
    if (!isEmpty()) {
        return stack[currentElem - 1];
    }

    return T();
}

}  // namespace CTL