#pragma once

#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static bool IS_OUTPUT_FILE_CREATED = false;

extern void createFile(fs::path &);
extern void deleteFile(fs::path &);

extern int getChoice();
extern int getYear(const std::string &);
extern std::string getDate(const std::string &);

extern bool isStreamValid();
extern bool isLeapYear(int);
extern bool isYearCorrect(const int &);
extern bool isDateCorrect(const std::string &);