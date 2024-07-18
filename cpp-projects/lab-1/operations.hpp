#pragma once

#include "functions.hpp"
#include "text.hpp"

extern void read_file();
extern void read_file(string);
extern void create_file();
extern void create_file(string);
extern void convert_file();
extern void write_to_file();
extern void delete_file();

extern void p_read_file();
extern void p_read_file(const char *);
extern void p_create_file();
extern void p_create_file(const char *);
extern void p_convert_file();
extern void p_write_to_file();
extern void p_delete_file();