#pragma once

#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <filesystem>

extern void createFile(std::filesystem::path &);
extern void deleteFile(std::filesystem::path &);

extern int getChoice();
extern int getYear(const std::string &);
extern std::string getDate(const std::string &);

extern bool isStreamValid();
extern bool isLeapYear(int);
extern bool isYearCorrect(const int &);
extern bool isDateCorrect(const std::string &);