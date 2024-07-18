# Lab 4

Overload operators. Fields. Getters. Setters. Namespaces.

## Task:

Define the class _"Triangle"_, with the sides of the triangle as fields.  Implement several constructors, getters, methods for calculating the area of ​​a triangle. Overload operators: 
- `++`/`--` - to increment/decrement the lengths of the sides,
- `+=`/`-=` - to increase/decrease the lengths of the sides of the triangle by the specified amount.

### Scenario:

1. Create three triangles __(T1, T2, T3)__ using different constructors.
2. Increment the lengths of the sides of triangle __T1__, and decrement the lengths of the sides of triangle __T2__. Increase the lengths of the sides of triangle __T3__ by the specified amount.
3. Find the triangle with the largest area.

## Getting Started

1. Navigate to the project directory:

    ```cmd
    cd .\lab-4
    ```

2. Build the program:

    ```cmd
    g++ .\main.cpp .\interface.cpp .\triangle.cpp -o main.exe
    ```

3. Launch the program:

    ```cmd
    .\main.exe
    ```