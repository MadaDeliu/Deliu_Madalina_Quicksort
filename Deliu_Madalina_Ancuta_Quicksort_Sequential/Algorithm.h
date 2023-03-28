#pragma once

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>

template <typename T>
class Algorithm {
public:
    virtual void sort(std::vector<T>& arr) = 0;
};

#endif