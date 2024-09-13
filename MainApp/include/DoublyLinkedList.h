#pragma once

#include <MPointer.h>

struct Node {
  int data; // Data stored in the node
  MPOINTER::MPointer<Node> next = nullptr; // Pointer to the next node
  MPOINTER::MPointer<Node> previous = nullptr; // Pointer to the previous node
};

class DoublyLinkedList {
public:
  /**
   * @brief Constructor
   */
  DoublyLinkedList();

  /**
   * @brief Destructor
   */
  ~DoublyLinkedList();

  /**
   * @brief Insert a new node in the list
   * @param value Value to insert
   */
  void insert(int value);

  /**
   * @brief Swap two nodes
   * @param a Node a
   * @param b Node b
   */
  static void swap(MPOINTER::MPointer<Node> a, MPOINTER::MPointer<Node> b);

  /**
   * @brief Overload the [] operator
   * @param index Index of the node
   * @return Node
   */
  MPOINTER::MPointer<Node> operator[](const int& index) const;

  /**
   * @brief Get the size of the list
   * @return Size of the list
   */
  [[nodiscard]] int getSize() const;

  /**
   * @brief Print the list
   */
  void printList() const;

private:
  MPOINTER::MPointer<Node> first = nullptr; // Pointer to the first node
  MPOINTER::MPointer<Node> last = nullptr; // Pointer to the last node
  int size; // Size of the list
};
