#pragma once

#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "colors.hpp"

using namespace std;

static const char *MARKS = ".:,;!?()\\";
static const int EXT_LENGTH = 4, MAX_FILENAME_LENGTH = 127, BUFFER_SIZE = 256;

extern bool open_file(ifstream &, string);
extern bool open_file(ofstream &, string);
extern bool open_file(fstream &, string);

extern void error_call(int);
extern bool has_control_chars(const string &);
extern bool is_name_taken(string);
extern bool is_name_forbidden(string);

extern string get_file_name(int);
extern string get_file_name();
extern int get_files_number();

extern void add_to_list(string);
extern void remove_from_list(string);
extern void display_file_names(int);
extern string choose_file();

extern char *extend_array(char *, char *);
extern int get_file_size(FILE *, const char *);
extern bool has_control_chars(const char *);
extern bool is_name_taken(const char *);
extern bool is_name_forbidden(const char *);

extern char *p_get_file_name(int);
extern char *p_get_file_name();
extern int p_get_files_number();
extern void p_add_to_list(const char *);
extern void p_remove_from_list(const char *);
extern char *p_choose_file();
