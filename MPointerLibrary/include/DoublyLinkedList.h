#pragma once
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
public:
    /**
     * @brief Constructor
     */
    DoublyLinkedList() noexcept: head(nullptr), tail(nullptr), size(0) {}

    /**
     * @brief Destructor
     */
    ~DoublyLinkedList() noexcept {
        const Node* current = head;

        while (current) {
            const Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }

    /**
     * @brief Insert a new node in the list
     * @param data Data to insert
     */
    void insert(const T& data) {
        auto* newNode = new Node(data);
        newNode->next = nullptr;

        if (!head) {
            newNode->prev = nullptr;
            head = tail = newNode;

        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    /**
     * @brief Swap two elements
     * @param a First element
     * @param b Second element
     */
    void swap(const T& a, const T& b) {
        Node* nodeA = find(a);
        Node* nodeB = find(b);

        if (nodeA && nodeB) {
            auto temp = *nodeA->data;
            nodeA->data = *nodeB->data;
            nodeB->data = temp;
        }
    }

    /**
     * @brief Get the data at the specified index
     * @param index Index of the data
     * @return Data at the specified index
     */
    T& operator[](const int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    /**
     * @brief Get the size of the list
     * @return Size of the list
     */
    [[nodiscard]] int getSize() const {
        return size;
    }

    /**
     * @brief Iterator class
     */
    class Iterator;

    /**
     * @brief Remove a node from the list
     * @param data Data to remove
     * @return Iterator to the next node
     */
    Iterator remove(const T& data) {
        Node* nodeToRemove = find(data);
        if (!nodeToRemove) {
            return end();
        }

        if (nodeToRemove == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
        } else if (nodeToRemove == tail) {
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            }
        } else {
            nodeToRemove->prev->next = nodeToRemove->next;
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
        Iterator nextNode(nodeToRemove->next);

        delete nodeToRemove;
        size--;

        return nextNode;
    }

    /**
     * @brief Get the beginning iterator
     * @return Iterator to the beginning
     */
    Iterator begin() {
        return Iterator(head);
    }

    /**
     * @brief Get the end iterator
     * @return Iterator to the end
     */
    Iterator end() {
        return Iterator(nullptr);
    }

private:
    /**
     * @brief Node structure
     */
    struct Node {
        T data; // Data stored in the node
        Node* next; // Pointer to the next node
        Node* prev; // Pointer to the previous node
    };

    /**
     * @brief Iterator class
     */
    class Iterator {
        /**
         * @brief Constructor
         * @param node Node to point to
         */
        explicit Iterator(Node* node): current(node) {}

        /**
         * @brief Get the data of the current node
         * @return Data of the current node
         */
        T& operator*() {
            return current->data;
        }

        /**
         * @brief Get the current node data
         * @return Data of the current node
         */
        T* operator->() {
            return &current->data;
        }

        /**
         * @brief Get the next node
         * @return Next node
         */
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        /**
         * @brief Get the previous node
         * @return Previous node
         */
        Iterator operator--() {
            current = current->prev;
            return *this;
        }

        /**
         * @brief Compare two iterators
         * @param other Other iterator to compare
         * @return True if the iterators are equal, false otherwise
         */
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        /**
         * @brief Compare two iterators
         * @param other Other iterator to compare
         * @return True if the iterators are different, false otherwise
         */
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Node* current; // Current node
    };

    /**
     * @brief Find a node in the list
     * @param data Data to find
     * @return Pointer to the node if found, nullptr otherwise
     */
    Node* find(const T& data) {
        Node* current = head;

        while (current) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }

    Node* head; // Pointer to the first node
    Node* tail; // Pointer to the last node
    int size; // Number of elements in the list
};
