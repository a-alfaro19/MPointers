#pragma once

#include "DoublyLinkedList.h"

namespace SORTALGORITHMS {
int partition(DoublyLinkedList& list, int low, int high);

void quickSort(DoublyLinkedList& list, int low, int high);

// void bubbleSort(DoublyLinkedList& list) {
//     const int size = list.getSize();
//     for (int i = 0; i < size - 1; i++) {
//         for (int j = 0; j < size - i - 1; j++) {
//             if (list[j]->value > list[j + 1]->value) {
//                 list.swap(list[j], list[j + 1]);
//             }
//         }
//     }
// }
//
// template <typename T>
// void insertionSort(DoublyLinkedList& list) {
//     const int size = list.getSize();
//     for (int i = 1; i < size; ++i) {
//         const auto key = list[i]->value;
//         int j = i - 1;
//
//         while (j >= 0 && list[j]->value > key) {
//             list[j + 1] = list[j];
//             j = j - 1;
//         }
//         list[j + 1]->value = key;
//     }
// }

}
