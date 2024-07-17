#pragma once

// #include <xmemory>
#include <iostream>
#include <limits>

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