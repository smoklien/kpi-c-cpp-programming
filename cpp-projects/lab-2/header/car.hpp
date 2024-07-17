#pragma once

#include "..\header\utils.hpp"

struct Car
{
    std::string name;
    std::string manufacture_date;
    std::string sales_start_date;
};

extern bool isCarNew(Car &);
extern bool isManufacturedAfterMinYear(const Car &, const int &);
extern bool parseDate(const std::string &, int &, int &, int &);

extern bool readCar(std::ifstream &, Car &);
extern bool writeCar(std::ofstream &, const Car &);
extern void addCar(const fs::path &);
extern void printCars(const fs::path &, const int &);
extern void printNewCars(const fs::path &, const fs::path &);