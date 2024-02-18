//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/linked_list/single_linked_list.hpp"

namespace CTL {

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Node* current = head;
    Node* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void SinglyLinkedList<T>::insert_beginning(T data) {
    Node* new_node = new Node(data, head);
    head = new_node;
}

template <typename T>
void SinglyLinkedList<T>::insert_at_position(T data, int pos) {
    if (pos == 0) {
        insert_beginning(data);
        return;
    }

    Node* current = head;
    for (int i = 1; i < pos && current != nullptr; i++) {
        current = current->next;
    }

    if (current != nullptr) {
        Node* newNode = new Node(data, current->next);
        current->next = newNode;
    }
}

template <typename T>
void SinglyLinkedList<T>::insert_end(T data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }
}

template <typename T>
T SinglyLinkedList<T>::read_beginning() {
    return head ? head->data : T();
}

template <typename T>
T SinglyLinkedList<T>::read_at_position(int pos) {
    Node* current = head;

    for (int i = 0; i < pos && current != nullptr; i++) {
        current = current->next;
    }

    return current ? current->data : T();
}

template <typename T>
T SinglyLinkedList<T>::read_end() {
    Node* current = head;

    if (!current) return T();

    while (current->next != nullptr) {
        current = current->next;
    }

    return current->data;
}

template <typename T>
void SinglyLinkedList<T>::delete_beginning() {
    if (head == nullptr) return T();

    Node* temp = head;
    T data = head->data;
    head = head->next;
    delete temp;
}

template <typename T>
void SinglyLinkedList<T>::delete_at_position(int pos) {
    if (pos == 0 && head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;

    for (int i = 1; i < pos && current != nullptr && current->next != nullptr;
         i++) {
        current = current->next;
    }

    if (current != nullptr && current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

template <typename T>
void SinglyLinkedList<T>::delete_end() {
    if (head == nullptr) return;

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;

    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
}

template <typename T>
int SinglyLinkedList<T>::search(std::function<int(T[], int, T)> searchMethod,
                                T key) {
    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    T* arr = new T[count];
    temp = head;

    for (int i = 0; i < count; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }

    int index = searchMethod(arr, count, key);

    delete[] arr;

    return index;
}

template <typename T>
void SinglyLinkedList<T>::sort(std::function<void(T[], int)> sortMethod) {
    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    T* arr = new T[count];
    temp = head;

    for (int i = 0; i < count; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }

    sortMethod(arr, count);

    temp = head;

    for (int i = 0; i < count; i++) {
        temp->data = arr[i];
        temp = temp->next;
    }

    delete[] arr;
}

}  // namespace CTL