//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/queue/queue.hpp"

namespace CTL {

template <typename T>
Queue<T>::Queue(int size) : size(size), front(-1), rear(-1) {
    queue = new T[this->size];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] queue;
}

template <typename T>
void Queue<T>::enqueue(T data) {
    if (isFull()) return;

    if (isEmpty()) front = 0;

    rear = (rear + 1) % size;
    queue[rear] = data;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) return T();  // Return default constructed value for T

    T data = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % size;

    return data;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return front == -1;
}

template <typename T>
bool Queue<T>::isFull() const {
    return (rear + 1) % size == front;
}

template <typename T>
T Queue<T>::peek() const {
    if (isEmpty()) return T();  // Return default constructed value for T

    return queue[front];
}

}  // namespace CTL