#include "QuicksortSequential.h"

void Quicksort::sort(std::vector<int>& arr) {
    int n = arr.size();
    quicksort(arr, 0, n - 1);
}

void Quicksort::quicksort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = arr[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            break;
        }

        std::swap(arr[i], arr[j]);
    }

    quicksort(arr, left, j);
    quicksort(arr, j + 1, right);
}