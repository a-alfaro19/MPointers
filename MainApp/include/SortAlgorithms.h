#pragma once

#include "DoublyLinkedList.h"

namespace SORTALGORITHMS {
template <typename T>
int partition(DoublyLinkedList<T>& list, const int low, int high) {
    T pivot = list[high];
    auto i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        auto value = *list[j];
        if (*list[j] <= *pivot) {
            i++;
            list.swap(list[i], list[j]);
        }
    }
    list.swap(list[i + 1], list[high]);
    return i + 1;
}

template <typename T>
void quickSort(DoublyLinkedList<T>& list, int low, int high) {
    if (low < high) {
        const int pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
        quickSort(list, pivot + 1, high);
    }
}

template <typename T>
void bubbleSort(DoublyLinkedList<T>& list) {
    const int size = list.getSize();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*list[j] > *list[j + 1]) {
                list.swap(list[j], list[j + 1]);
            }
        }
    }
}

template <typename T>
void insertionSort(DoublyLinkedList<T>& list) {
    const int size = list.getSize();
    for (int i = 1; i < size; ++i) {
        auto key = *list[i];
        int j = i - 1;

        while (j >= 0 && *list[j] > key) {
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
}

}
