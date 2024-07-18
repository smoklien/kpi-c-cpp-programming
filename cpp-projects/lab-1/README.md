# Lab #1

Work with files. File streams. File pointers. Input arguments. Function overloads. Headers.

## Task:

Create text file. Words should be separated with spaces, comas and periods. Every even line of the input file have to be rewritten into a new tex file, transforming each word of such a line by replacing all previous occurrences of the last letter of the word with the symbol ".". For example, the word __"MINIMUM"__ must be converted to __".INI.UM"__. In odd lines of input text, remove words which contain the last letter of the first word of that line. Display the contents of the input, changed and new files.

### Requirements

Program have to be written in two possible modes:

- `FilePointer`: all the logic of the program's work with files have to be written using __pointers__ e.g. `FILE*`.
- `FileStream`: same as prevoius but with __file streams__, e.g. `ifstream`/`ofstream`.

## Getting started

1. Navigate to the project directory:

    ```cmd
    cd .\lab-1
    ```

2. Build the program:

    ```cmd
    g++ .\main.cpp .\functions.cpp .\operations.cpp .\text.cpp -o main.exe
    ```

3. Launch the program:

    `FilePointer` mode:

    -    
        ```cmd
        .\main.exe -mode FilePointer
        ```

    `FileStream` mode:

    -    
        ```cmd
        .\main.exe -mode FileStream
        ```