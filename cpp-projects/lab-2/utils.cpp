#include "utils.hpp"

void createFile(std::filesystem::path &file_path)
{
    std::ifstream file(file_path, std::ios::binary | std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Failed to create file: " << file_path << std::endl;
        return;
    }

    file.close();
}

void deleteFile(std::filesystem::path &file_path)
{
    if (!std::filesystem::remove(file_path))
    {
        std::cerr << "Error: Failed to delete the file: " << file_path << std::endl;
        return;
    }
}

bool isStreamValid()
{
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

            std::cerr << "Error: Invalid input. Please enter string." << std::endl;
        }
        return false;
    }
    return true;
}

bool isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool isDateCorrect(const std::string &date)
{
    if (date.length() != 10)
    {
        std::cerr << "Invalid date format. Expected format: dd-mm-yyyy" << std::endl;
        return false;
    }

    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (date[2] != '-' || date[5] != '-')
    {
        std::cerr << "Invalid date format. Expected format: dd-mm-yyyy" << std::endl;
        return false;
    }

    if (day < 1 || day > 31)
    {
        std::cerr << "Invalid day. Day must be between 1 and 31." << std::endl;
        return false;
    }

    if (month < 1 || month > 12)
    {
        std::cerr << "Invalid month. Month must be between 1 and 12." << std::endl;
        return false;
    }

    if (year < 1 || year > 9999)
    {
        std::cerr << "Invalid year. Year must be between 1 and 9999." << std::endl;
        return false;
    }

    if (month == 2)
    {
        bool isLeap = isLeapYear(year);
        if ((isLeap && day > 29) || (!isLeap && day > 28))
        {
            std::cerr << "Invalid day for February." << std::endl;
            return false;
        }
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        std::cerr << "Invalid day for the given month." << std::endl;
        return false;
    }
    return true;
}

bool isYearCorrect(const int &year)
{
    if (year < 1 || year > 9999)
    {
        std::cout << "Error: Invalid year. Year must be between 1 and 9999." << std::endl;
        return false;
    }
    return true;
}

std::string getDate(const std::string &promt)
{
    std::string date;

    while (true)
    {
        std::cout << promt;
        std::cin >> date;

        if (isStreamValid() && isDateCorrect(date))
        {
            break;
        }
    }

    return date;
}

int getYear(const std::string &promt)
{
    int year;

    while (true)
    {
        std::cout << promt;
        std::cin >> year;

        if (isStreamValid() && isYearCorrect(year))
        {
            break;
        }
    }

    return year;
}

int getChoice()
{
    int choice;

    while (true)
    {
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (isStreamValid())
        {
            break;
        }
    }

    return choice;
}