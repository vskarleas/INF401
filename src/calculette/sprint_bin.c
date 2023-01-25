/**************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble        */
/* 20/12/2007                                                 */
/*                                                            */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "sprint_bin.h"
#include "global.h"

char *margin;
char *lineres;

static char line [] =  "---------------------------------------------------";
static char spaces [] = "                                                                       ";
static char tens [] = "3322222222221111111111          ";
static char units   [] = "10987654321098765432109876543210";


/****************************************************************/
/* Define margin width                                          */
/****************************************************************/

void set_margin(unsigned int width)
  {
    margin = spaces + strlen(spaces) - width;
  }

/****************************************************************/
/* Display bits numbers                                         */
/****************************************************************/

void bits_numbers (void)
  {
  int delta = strlen(units) - number_of_bits;
  lineres   = line + strlen(line) - number_of_bits;
  printf ("%sBit numbers\n",margin);
  if (number_of_bits > 10) 
     { 
     printf ("%s", margin); 
     print_string (tens+delta);
     printf ("\n");
     }
  printf ("%s", margin);
  print_string (units+delta);
  }


/****************************************************************/
/* truncate integers according to the number of bits            */
/****************************************************************/

void truncate (unsigned int *value)
  {
  int v;
  v = *(int *) value;
  if ((number_of_bits > 0) && (number_of_bits <32)) 
     {
     v =  v & ((1 << number_of_bits) -1);
     *value = v;
     }
  }

/****************************************************************/
/* print chars four by four with spaces                         */
/****************************************************************/

void print_string (char *string)
  {
  int written;
  written = 4 - (strlen (string) %4);
  while (*string != 0)
    {
    putchar (*string++);
    written ++;
    if ((written % 4) == 0) putchar (' ');
    }
  }

/****************************************************************/
/* print integers in binary format                              */
/* Same as sprint ("%x") for binary format                      */
/* printf only nb_bits                                          */
/****************************************************************/

void sprint_bin(char *string, int x, int nb_bits, int spaces)
   {
   int i;
   int written;
   written = 4 - (nb_bits % 4);
   for (i=0; i<nb_bits; i++)
     {
     if (x < 0) 
        *string++ = '1';
     else
        *string++ = '0';
     written ++;
     if ((spaces) && ((written % 4) == 0)) *string++ = ' ';
     x <<= 1;
     }
   *string = 0;
   }
   
void print_bin(int x)
  {
  char c[50];
  sprint_bin(c,x, number_of_bits,1);
  printf("%s",c);
  }

