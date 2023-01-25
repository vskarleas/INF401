#ifndef STRING_TO_INT_H
#define STRING_TO_INT_H

#include <stdio.h>

void get_string (FILE *stream, char *readres, char *message_print);
int binary_to_int (const char *string, unsigned int *readres);
char *strip (char *string);
void tolowercase (char * c);
void do_string_to_int (char *string, unsigned int *value, 
                       char *error_message);
void string_to_int (char *string, unsigned int *value, 
                    char *error_message);
#endif
