#pragma once

#include "DoublyLinkedList.h"

namespace SORTALGORITHMS {

int partition(const DoublyLinkedList& list, int low, int high);

void quickSort(DoublyLinkedList& list, int low, int high);

void bubbleSort(const DoublyLinkedList& list);

void insertionSort(const DoublyLinkedList& list);

}
