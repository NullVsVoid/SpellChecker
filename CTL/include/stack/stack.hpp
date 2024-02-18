//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#ifndef STACK_HPP
#define STACK_HPP

namespace CTL {

template <typename T>
class Stack {
   private:
    int size;
    int currentElem = 0;
    T* stack;

   public:
    explicit Stack(int size = 100);
    ~Stack();

    void push(T data);
    T pop();
    bool isEmpty() const;
    bool isFull() const;
    T peek() const;
};

}  // namespace CTL

#include "../../src/stack/stack.cpp"

#endif  // STACK_HPP