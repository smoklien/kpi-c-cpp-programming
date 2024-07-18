#include "..\header\array.hpp"

void createArrays(NumericArray **, int);
void printMaxArray(NumericArray **, int);
void deleteArrays(NumericArray **, int);
bool askForRestart();
int askForArrayCount();

int main()
{
    do
    {
        try
        {
            srand(time(0));

            int array_count = askForArrayCount();
            NumericArray **arrays = new NumericArray *[array_count];

            createArrays(arrays, array_count);
            printMaxArray(arrays, array_count);
            deleteArrays(arrays, array_count);

            delete[] arrays;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
        }
    } while (askForRestart());

    return 0;
}
//
// Create and print arrays
//
void createArrays(NumericArray **arrays, int array_count)
{
    for (int i = 0; i < array_count; i++)
    {
        std::cout << std::endl;
        std::cout << "Array number " << i + 1 << std::endl;
        arrays[i] = new NumericArray(10);
        arrays[i]->printArray();
    }
    std::cout << std::endl;
}
//
// Print array with minimal maximum element
//
void printMaxArray(NumericArray **arrays, int array_count)
{
    NumericArray *min_max_array = arrays[0];
    int min_max = arrays[0]->getMaxElement();
    int min_max_array_index = 0;

    for (int i = 1; i < array_count; i++)
    {
        int current_max = arrays[i]->getMaxElement();
        if (current_max < min_max)
        {
            min_max = current_max;
            min_max_array = arrays[i];
            min_max_array_index = i;
        }
    }

    std::cout << std::endl;
    std::cout << "Array number " << min_max_array_index + 1 << " contains the least maximum element" << std::endl;
    min_max_array->printArray();
}
//
// Free memory
//
void deleteArrays(NumericArray **arrays, int array_count)
{
    for (int i = 0; i < array_count; ++i)
    {
        delete arrays[i];
    }
}
//
// Util for restart prog
//
bool askForRestart()
{
    char input;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "Would you like to restart the program? (y/n): ";
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: invalid input. Please try again." << std::endl;
        }
        else
        {
            break; // Input is valid, exit the loop
        }
    }

    return (input == 'Y' || input == 'y');
}
//
// Get amount of arrays from user
//
int askForArrayCount()
{
    int array_count;

    while (true)
    {
        std::cout << "Enter the count of numeric arrays: ";
        std::cin >> array_count;

        if (std::cin.fail() || std::cin.peek() != '\n')
        {
            if (std::cin.eof())
            {
                std::cin.clear();
                std::cerr << "Error: Unexpected end of input" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Error: Invalid input. Please enter a numeric value." << std::endl;
            }
        }
        else if (array_count < 1)
        {
            std::cerr << "Error: Array count cannot be less than 1." << std::endl;
        }
        else if (array_count > 9999)
        {
            std::cerr << "Error: Array count is too big. Maximum value is 9999." << std::endl;
        }
        else
        {
            break; // Input is valid, exit the loop
        }
    }

    return array_count;
}