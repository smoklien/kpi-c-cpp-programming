# Lab 5

Inheritance. Virtual functions. Override.

## Task:

Create a __TIntNumber__ class that represents an integer in any system counting and contains methods for incrementing / decrementing a number and converting a number into the decimal. Based on this class create inhereted classes __TIntNumber2__ and __TIntNumber16__ representing binary and hexadecimal numbers. 

### Scenario:

1. Generate `m` binary and `n` hexadecimal numbers. 
2. Increment binary numbers.
3. decrement hexadecimal numbers.
4. Convert numbers to decimals.
5. find the largest number.

## Getting Started

1. Navigate to the project directory:

    ```cmd
    cd .\lab-5
    ```

2. Build the program:

    ```cmd
    g++ .\main.cpp .\interface.cpp .\numbers.cpp .\hex_numbers.cpp .\binary_numbers.cpp -o main.exe
    ```

3. Launch the program:

    ```cmd
    .\main.exe
    ```