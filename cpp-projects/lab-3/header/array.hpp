#pragma once

#include <limits>
#include <iostream>

class NumericArray {
private:
    int* arr;
    int size;

public:
    NumericArray(int);
    ~NumericArray();

    int getMaxElement();
    void printArray();
};