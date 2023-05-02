#include "QuicksortParallel.h"


void QuicksortParallel::quicksort_parallel(std::vector<int>& arr, int left, int right) {
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

#pragma omp task
    {
        quicksort_parallel(arr, left, j);
    }
#pragma omp task
    {
        quicksort_parallel(arr, j + 1, right);
    }
}
