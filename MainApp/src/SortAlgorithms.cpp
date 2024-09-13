#include <SortAlgorithms.h>

namespace SORTALGORITHMS {
int partition(const DoublyLinkedList& list, const int low, const int high) {
    const int pivot = list[high]->data;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (list[j]->data <= pivot) {
            i++;
            DoublyLinkedList::swap(list[i], list[j]);
        }
    }
    DoublyLinkedList::swap(list[i + 1], list[high]);
    return i + 1;
}

void quickSort(DoublyLinkedList& list, const int low, const int high) {
    if (low < high) {
        const int pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
        quickSort(list, pivot + 1, high);
    }
}

void bubbleSort(const DoublyLinkedList &list) {
    const int size = list.getSize();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j]->data > list[j + 1]->data) {
                DoublyLinkedList::swap(list[j], list[j + 1]);
            }
        }
    }
}

void insertionSort(const DoublyLinkedList &list) {
    const int size = list.getSize();
    for (int i = 1; i < size; i++) {
        const auto key = list[i]->data;
        int j = i - 1;

        while (j >= 0 && list[j]->data > key) {
            list[j + 1]->data = list[j]->data;
            j = j - 1;
        }
        list[j + 1]->data = key;
    }
}



}