#pragma once

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Algorithm.h"

class Quicksort : public Algorithm<int> {
public:
    void sort(std::vector<int>& arr);
private:
    void quicksort(std::vector<int>& arr, int left, int right);
};

#endif