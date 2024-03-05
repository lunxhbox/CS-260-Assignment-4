#include <iostream>
#include <stdexcept>

// Node class represents each node in the linked list
template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    // Constructor to initialize node with data value
    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList class represents the linked list data structure
template<typename T>
class LinkedList {
private:
    Node<T>* head;  // Pointer to the head of the linked list
    int size;       // Size of the linked list

public:
    // Constructor to initialize an empty linked list
    LinkedList() : head(nullptr), size(0) {}

    // Destructor to free memory occupied by nodes
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Method to add an element at a specified position in the linked list
    void add(T value, int position) {
        if (position < 0 || position > size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* newNode = new Node<T>(value);
        if (position == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Method to remove an element from a specified position in the linked list
    T remove(int position) {
        if (position < 0 || position >= size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* temp = nullptr;
        if (position == 0) {
            temp = head;
            head = head->next;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            temp = current->next;
            current->next = temp->next;
        }
        T value = temp->data;
        delete temp;
        size--;
        return value;
    }

    // Method to retrieve the value at a specified position in the linked list
    T get(int position) {
        if (position < 0 || position >= size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current->data;
    }
};

// Main function to demonstrate the usage of the LinkedList class
int main() {
    LinkedList<int> myList;
    myList.add(1, 0);
    myList.add(2, 1);
    myList.add(3, 2);

    std::cout << "Element at position 1: " << myList.get(1) << std::endl; // Should print 2
    std::cout << "Remove element at position 0: " << myList.remove(0) << std::endl; // Should print 1
    std::cout << "Element at position 0 after removal: " << myList.get(0) << std::endl; // Should print 2

    myList.add(4, 1);
    std::cout << "Element at position 1 after insertion: " << myList.get(1) << std::endl; // Should print 4

    return 0;
}
