//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace CTL {

template <typename T>
class Queue {
   private:
    int size;
    int front;
    int rear;
    T* queue;

   public:
    explicit Queue(int size = 100);
    ~Queue();

    void enqueue(T data);
    T dequeue();
    bool isEmpty() const;
    bool isFull() const;
    T peek() const;
};

}  // namespace CTL

#include "../../src/queue/queue.cpp"

#endif  // QUEUE_HPP