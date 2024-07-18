#include "..\header\array.hpp"

NumericArray::NumericArray(int size) : size(size)
{
    arr = new int[size];

    for (int i = 0; i < size; ++i)
    {
        // Filling array with random numbers from 0 to 99
        arr[i] = rand() % 100;
    }
}

NumericArray::~NumericArray()
{
    delete[] arr;
}

int NumericArray::getMaxElement()
{
    int max = arr[0];

    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

void NumericArray::printArray()
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}