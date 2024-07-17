#include "..\header\car.hpp"
#include "..\header\utils.hpp"

void menu(fs::path, fs::path);

int main()
{
    fs::path current_path = fs::current_path();
    fs::path file_path = current_path / "cars.bin";
    fs::path output_file_path = current_path / "cars_new.bin";

    createFile(file_path);
    menu(file_path, output_file_path);
    deleteFile(file_path);
    if(IS_OUTPUT_FILE_CREATED == true)
    {
        deleteFile(output_file_path);
    }

    return 0;
}

void menu(fs::path file_path, fs::path output_file_path)
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
            IS_OUTPUT_FILE_CREATED = true;
            printNewCars(file_path, output_file_path);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice\n";
        }
    }
}