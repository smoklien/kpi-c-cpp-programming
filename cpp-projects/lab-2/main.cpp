#include "car.hpp"
#include "utils.hpp"

void menu(std::filesystem::path);

int main()
{
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path file_path = current_path / "cars.bin";
    // std::string file_name = "cars.bin";

    createFile(file_path);
    menu(file_path);
    deleteFile(file_path);

    return 0;
}

void menu(std::filesystem::path file_path)
{
    while (true)
    {
        int choice;

        std::cout << "\n--- Car Dealership Menu ---\n\n";
        std::cout << "1. Add car\n";
        std::cout << "2. Print cars from specified year\n";
        std::cout << "3. Print new cars\n";
        std::cout << "0. Exit\n";

        choice = getChoice();

        int min_year;

        switch (choice)
        {
        case 1:
            addCar(file_path);
            break;
        case 2:
            min_year = getYear("Enter minimum year (yyyy): ");
            printCars(file_path, min_year);
            break;
        case 3:
            printNewCars(file_path);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice\n";
        }
    }
}