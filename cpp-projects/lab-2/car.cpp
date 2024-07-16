#include "car.hpp"

bool isCarNew(Car &car)
{
    [[maybe_unused]] int _; // Declare a dummy variable
    int sales_month, manufacture_month;
    int sales_year, manufacture_year;

    parseDate(car.sales_start_date, _, sales_month, sales_year);
    parseDate(car.manufacture_date, _, manufacture_month, manufacture_year);

    if (sales_month - manufacture_month <= 2 && sales_year == manufacture_year)
    {
        return true;
    }
    return false;
}

bool isManufacturedAfterMinYear(const Car &car, const int &min_year)
{
    [[maybe_unused]] int _; // Declare a dummy variable
    int manufacture_year;

    parseDate(car.manufacture_date, _, _, manufacture_year);

    if (manufacture_year >= min_year)
    {
        return true;
    }
    return false;
}

bool parseDate(const std::string &dateString, int &day, int &month, int &year)
{
    std::istringstream iss(dateString);
    char delimiter;

    if (iss >> day >> delimiter >> month >> delimiter >> year)
    {
        return true;
    }
    return false;
}

void addCar(const std::filesystem::path &file_path)
{
    std::string name, manufacture_date, sales_start_date;

    std::cout << "Enter car name: ";
    std::cin >> name;

    manufacture_date = getDate("Enter manufacture date (dd-mm-yyyy): ");
    sales_start_date = getDate("Enter sales start date (dd-mm-yyyy): ");

    int manufacture_day, manufacture_month, manufacture_year;
    int sales_day, sales_month, sales_year;

    if (!parseDate(manufacture_date, manufacture_day, manufacture_month, manufacture_year) ||
        !parseDate(sales_start_date, sales_day, sales_month, sales_year))
    {
        std::cerr << "Error: Invalid date format." << std::endl;
        return;
    }

    if (sales_year < manufacture_year ||
        (sales_year == manufacture_year && sales_month < manufacture_month) ||
        (sales_year == manufacture_year && sales_month == manufacture_month && sales_day < manufacture_day))
    {
        std::cerr << "Error: Sales start day cannot be earlier than the manufacture date." << std::endl;
        return;
    }

    Car car{name, manufacture_date, sales_start_date};

    std::ofstream file(file_path, std::ios::binary | std::ios::app);
    if (!file)
    {
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return;
    }

    if (!writeCar(file, car))
    {
        std::cerr << "Error: Failed to write car data to file." << std::endl;
        return;
    }

    file.close();
    std::cout << "Car added successfully!" << std::endl;
}

bool readCar(std::ifstream &file, Car &car)
{
    std::size_t name_size, manufacture_date_size, sales_start_date_size;

    if (!file.read(reinterpret_cast<char *>(&name_size), sizeof(std::size_t)))
    {
        return false;
    }

    car.name.resize(name_size);
    if (!file.read(&car.name[0], name_size))
    {
        return false;
    }

    if (!file.read(reinterpret_cast<char *>(&manufacture_date_size), sizeof(std::size_t)))
    {
        return false;
    }

    car.manufacture_date.resize(manufacture_date_size);
    if (!file.read(&car.manufacture_date[0], manufacture_date_size))
    {
        return false;
    }

    if (!file.read(reinterpret_cast<char *>(&sales_start_date_size), sizeof(std::size_t)))
    {
        return false;
    }

    car.sales_start_date.resize(sales_start_date_size);
    if (!file.read(&car.sales_start_date[0], sales_start_date_size))
    {
        return false;
    }

    return true;
}

bool writeCar(std::ofstream &file, const Car &car)
{
    std::size_t name_size = car.name.size();
    if (!file.write(reinterpret_cast<const char *>(&name_size), sizeof(std::size_t)))
    {
        return false;
    }
    if (!file.write(car.name.c_str(), name_size))
    {
        return false;
    }

    std::size_t manufacture_date_size = car.manufacture_date.size();
    if (!file.write(reinterpret_cast<const char *>(&manufacture_date_size), sizeof(std::size_t)))
    {
        return false;
    }
    if (!file.write(car.manufacture_date.c_str(), manufacture_date_size))
    {
        return false;
    }

    std::size_t sales_start_date_size = car.sales_start_date.size();
    if (!file.write(reinterpret_cast<const char *>(&sales_start_date_size), sizeof(std::size_t)))
    {
        return false;
    }
    if (!file.write(car.sales_start_date.c_str(), sales_start_date_size))
    {
        return false;
    }

    return true;
}

void printCars(const std::filesystem::path &filename, const int &min_year)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Failed to open file for reading." << std::endl;
        return;
    }

    Car car;

    bool success;
    while (success = readCar(file, car))
    {
        if (isManufacturedAfterMinYear(car, min_year))
        {
            std::cout << "Car: " << car.name << ", Manufacture date: " << car.manufacture_date << ", Sales start date: " << car.sales_start_date << std::endl;
        }
    }
    if (!success || file.eof() || file.fail())
    {
        std::cerr << "Error: Failed to read car data from the input file." << std::endl;
        return;
    }

    file.close();
}

void printNewCars(const std::filesystem::path &file_path)
{
    std::filesystem::path output_file_path = file_path + "_new.bin";

    std::ifstream file(file_path, std::ios::binary);
    std::ofstream output_file(output_file_path, std::ios::binary);

    if (!file)
    {
        std::cerr << "Error: Failed to open input file for reading." << std::endl;
        return;
    }

    if (!output_file)
    {
        std::cerr << "Error: Failed to open output file for writing." << std::endl;
        return;
    }

    Car car;

    bool success;
    while (success = readCar(file, car))
    {
        if (isCarNew(car))
        {
            output_file << "Car: " << car.name << ", Manufacture date: " << car.manufacture_date << ", Sales start date: " << car.sales_start_date << "\n";
            std::cout << "Car: " << car.name << ", Manufacture date: " << car.manufacture_date << ", Sales start date: " << car.sales_start_date << "\n";
        }
    }
    if (!success || file.eof() || file.fail())
    {
        std::cerr << "Error: Failed to read car data from." << file_path << std::endl;
        return;
    }

    file.close();
    output_file.close();
}