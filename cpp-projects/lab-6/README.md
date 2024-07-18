# Lab 6

Abstract Data Types. Array. Iterators. Templates.

## Task:

Create an abstract data type (`ADT`) _"Array with defined size"_ that contains data of an arbitrary type. The `ADT` interface have to include next operations:

- Define the array size.
- Search for an element with a given value.
- Check the array for emptiness.
- Add the new element to the given position.
- An iterator with next operations:
    1. Setting to the beginning of the array.
    2. Checking the end of the array.
    3. Access to the current value of the array.
    4. Transition to the next element of the array.

## Getting Started

1. Navigate to the project directory:

    ```cmd
    cd .\lab-6
    ```

2. Build the program:

    ```cmd
    g++ .\main.cpp .\interface.cpp .\array.cpp -o main.exe
    ```

3. Launch the program:

    ```cmd
    .\main.exe
    ```