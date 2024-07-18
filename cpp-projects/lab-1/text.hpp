#pragma once

#include "functions.hpp"

extern void replace_letter(string &, char);
extern void replace_letter(char *, char);

extern void delete_word(string &, char);
extern char *delete_word(char *, char);

extern string edit_even_line(string);
extern char *edit_even_line(char *);

extern string edit_odd_line(string);
extern char *edit_odd_line(char *);