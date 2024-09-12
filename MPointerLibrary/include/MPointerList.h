#pragma once

namespace MPOINTER {

/**
 * MPointer Info
 */
struct PointerInfo {
 void* pointer;
 int refCount;
 int id;
};

/**
 * @brief Node structure
 */
struct Node {
 PointerInfo data; // Data stored in the node
 Node* next; // Pointer to the next node
 Node* previous; // Pointer to the previous node
};

class MPointerList {
public:
 /**
  * @brief Constructor
  */
 MPointerList() noexcept;

 /**
  * @brief Destructor
  */
 ~MPointerList() noexcept;

 /**
  * @brief Insert a new node in the list
  * @param data Data to insert
  */
 void insert(const PointerInfo& data);

 /**
  * @brief Get the size of the list
  * @return Size of the list
  */
 [[nodiscard]] int getSize() const;

 /**
  * @brief Remove the unused pointers
  */
 void removeUnusedPointers();

 /**
 * @brief Find a node in the list
 * @param id ID of the pointer to find
 * @return Pointer to the node if found, nullptr otherwise
 */
 [[nodiscard]] PointerInfo* find(int id) const;

 /**
  * @brief Clear the list
  */
 void clear();

 /**
  * @brief Print the list
  */
 void printList() const;

private:
 Node* head; // Pointer to the first node
 Node* tail; // Pointer to the last node
 int size; // Number of elements in the list
};

}