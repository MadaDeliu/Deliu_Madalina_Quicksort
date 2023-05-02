#pragma once

#ifndef QUICKSORT_PARALLEL_H
#define QUICKSORT_PARALLEL_H

#include "Algorithm.h"

class QuicksortParallel{

public:
    static void quicksort_parallel(std::vector<int>& arr, int left, int right);
};

#endif