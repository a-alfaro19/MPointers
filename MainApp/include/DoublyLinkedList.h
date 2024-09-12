#pragma once

#include <MPointer.h>

struct Node {
  int data;
  MPOINTER::MPointer<Node> next = nullptr;
  MPOINTER::MPointer<Node> previous = nullptr;
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
  void swap(MPOINTER::MPointer<Node> a, MPOINTER::MPointer<Node> b);

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
  MPOINTER::MPointer<Node> first = nullptr;
  MPOINTER::MPointer<Node> last = nullptr;
  int size;
};
