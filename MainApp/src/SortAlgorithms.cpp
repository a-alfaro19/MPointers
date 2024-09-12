#include <SortAlgorithms.h>

namespace SORTALGORITHMS {
int partition(DoublyLinkedList& list, const int low, const int high) {
    const int pivot = list[high]->data;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (list[j]->data <= pivot) {
            i++;
            list.swap(list[i], list[j]);
        }
    }
    list.swap(list[i + 1], list[high]);
    return i + 1;
}

void quickSort(DoublyLinkedList& list, const int low, const int high) {
    if (low < high) {
        const int pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
        quickSort(list, pivot + 1, high);
    }
}

}