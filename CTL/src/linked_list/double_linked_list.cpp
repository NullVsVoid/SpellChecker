//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include "../../include/linked_list/double_linked_list.hpp"

namespace CTL {

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert_beginning(T data) {
    Node* newNode = new Node(data);
    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail =
            newNode;  // If the list was empty, tail also points to the new node
    }
    head = newNode;
}

template <typename T>
void DoublyLinkedList<T>::insert_at_position(T data, int pos) {
    if (pos == 0) {
        insert_beginning(data);
        return;
    }

    Node* temp = head;
    for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) return;  // Position is out of bounds

    Node* newNode = new Node(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    } else {
        tail = newNode;  // Inserting at the end
    }

    temp->next = newNode;
}

template <typename T>
void DoublyLinkedList<T>::insert_end(T data) {
    Node* newNode = new Node(data);

    if (tail != nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
    } else {
        head = newNode;  // The list was empty
    }
    tail = newNode;
}

template <typename T>
T DoublyLinkedList<T>::read_beginning() {
    return head ? head->data : T();
}

template <typename T>
T DoublyLinkedList<T>::read_at_position(int pos) {
    Node* temp = head;

    for (int i = 0; i < pos && temp != nullptr; i++) {
        temp = temp->next;
    }

    return temp ? temp->data : T();
}

template <typename T>
T DoublyLinkedList<T>::read_end() {
    return tail ? tail->data : T();
}

template <typename T>
void DoublyLinkedList<T>::delete_beginning() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;

    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;  // List became empty
    }

    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::delete_at_position(int pos) {
    if (pos == 0) {
        delete_beginning();
        return;
    }

    Node* temp = head;
    for (int i = 0; i < pos && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) return;  // Position is out of bounds

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;  // Deleting the last node
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }

    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::delete_end() {
    if (tail == nullptr) return;

    Node* temp = tail;
    tail = tail->prev;

    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;  // List became empty
    }

    delete temp;
}

template <typename T>
int DoublyLinkedList<T>::search(std::function<int(T[], int, T)> searchMethod,
                                T key) {
    int size = 0;
    Node* temp = head;

    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    if (size == 0) return -1;

    T* arr = new T[size];
    temp = head;

    for (int i = 0; i < size; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }

    int index = searchMethod(arr, size, key);

    delete[] arr;

    return index;
}

template <typename T>
void DoublyLinkedList<T>::sort(std::function<void(T[], int)> sortMethod) {
    int size = 0;
    Node* temp = head;

    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    if (size <= 1) return;

    T* arr = new T[size];
    temp = head;

    for (int i = 0; i < size; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }

    sortMethod(arr, size);

    temp = head;
    for (int i = 0; i < size; i++) {
        temp->data = arr[i];
        temp = temp->next;
    }

    delete[] arr;
}

}  // namespace CTL