#ifndef INCLUDE_SPRINT_BIN_H
#define INCLUDE_SPRINT_BIN_H

extern char *margin;
extern char *lineres;

void set_margin(unsigned int width);
void bits_numbers (void);
void truncate (unsigned int *value);
void print_string (char *string);
void sprint_bin(char *string, int x, int nb_bits, int spaces);
void print_bin(int x);
#endif
