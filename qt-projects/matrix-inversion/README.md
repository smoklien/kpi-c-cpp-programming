# Matrix Inversion

Course work. Matrices. GUI. QT Framework. Windows. Inversion. LU decomposition. Blockwise inversion. Matrices Multiplying. Recursions. Determinants. Signals. File Explorer.

## Task:

Create a program that performs matrix inversion using two methods:

- [LU decompose](https://en.wikipedia.org/wiki/LU_decomposition#Inverting_a_matrix)
- [Blockwise Inversion](https://en.wikipedia.org/wiki/Invertible_matrix#Blockwise_inversion)

In case of date format inconsistency or its incorrectness, generate appropriate exceptional situations and organize their processing. Create Graphic User Interface _(GUI)_ for this task with data input and output. Make it possible to save the result to the device. Program also should has random number generator.

### Scenario:

1. The program receives from the user a square matrix of real numbers named `A` in size from _1_ to _10_. The matrix look like this:

$$
A=
\begin{pmatrix}
   a_{11} & \cdots & a_{1n} \\
   \cdots & \ddots & \cdots \\
   a_{m1} & \cdots & a_{mn} 
\end{pmatrix}
$$

2. User choose the method of inversion and choose whether they want to generate it randomly.
3. Second window displays if the user chose a manual method.
4. The last window shows the original matrix and the inverted one with an option to read about the algorithm and to save a result into a text file.

## Getting Started

### Windows 11, MinGW

1. Download QT binaries from the [online installer](https://www.qt.io/download-qt-installer-oss)
2. Open the QT MinGW's terminal and Navigate to the `realese` directory:

```batch
cd kpi-c-cpp-programming\qt-projects\matrix-inversion\release
```

3. Run the `windeployqt` command to create a deployable folder containing the Qt-related dependencies:

```batch
windeployqt matrix-inversion.exe
```

4. Run the executable:

```batch
matrix-inversion.exe
```
