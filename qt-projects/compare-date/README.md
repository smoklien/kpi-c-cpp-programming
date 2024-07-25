# Lab 7

Compare date project. GUI. QT Framework. Windows. Regular Expressions. Signals.

## Task:

Create _"Date"_ class with date format DD-MM-YYYY. In case of date format inconsistency or its incorrectness, generate appropriate exceptional situations and organize their processing. Create Graphic User Interface _(GUI)_ for this task. With data input and output.

### Scenario:

1. Create two date objects.
2. Find the older one.

## Getting Started

### Windows 11, MinGW

1. Download QT binaries from the [online installer](https://www.qt.io/download-qt-installer-oss)
2. Open the QT MinGW's terminal and Navigate to the `realese` directory:

```batch
cd kpi-c-cpp-programming\qt-projects\matrix-inversion\release
```

3. Run the `windeployqt` command to create a deployable folder containing the Qt-related dependencies:

```batch
windeployqt compare-date.exe
```

4. Run the executable:

```batch
compare-date.exe
```
