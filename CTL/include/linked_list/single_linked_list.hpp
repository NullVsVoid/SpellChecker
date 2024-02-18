//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#ifndef SINGLE_LINKED_LIST_HPP
#define SINGLE_LINKED_LIST_HPP

#include <functional>

namespace CTL {

template <typename T>
class SinglyLinkedList {
   private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head = nullptr;

   public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList();

    void insert_beginning(T data);
    void insert_at_position(T data, int pos);
    void insert_end(T data);

    T read_beginning();
    T read_at_position(int pos);
    T read_end();

    void delete_beginning();
    void delete_at_position(int pos);
    void delete_end();

    int search(std::function<int(T[], int, T)> searchMethod, T key);
    void sort(std::function<void(T[], int)> sortMethod);
};

}  // namespace CTL

#include "../../src/linked_list/single_linked_list.cpp"

#endif  // SINGLE_LINKED_LIST_HPP
