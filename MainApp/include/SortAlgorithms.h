#pragma once

#include "DoublyLinkedList.h"

namespace SORTALGORITHMS {

/**
 * @brief Partition the list
 * @param list List to partition
 * @param low Low index
 * @param high High index
 * @return Index of the partition
 */
int partition(const DoublyLinkedList& list, int low, int high);

/**
 * @brief Quick sort algorithm
 * @param list List to sort
 * @param low Low index
 * @param high High index
 */
void quickSort(DoublyLinkedList& list, int low, int high);

/**
 * @brief Bubble sort algorithm
 * @param list List to sort
 */
void bubbleSort(const DoublyLinkedList& list);

/**
 * @brief Insertion sort algorithm
 * @param list List to sort
 */
void insertionSort(const DoublyLinkedList& list);

}
