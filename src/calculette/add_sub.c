/***************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble         */
/* 20/12/2007                                                  */
/***************************************************************/

#include "add_sub.h"
#include "global.h"

char *format;

typedef void fdetail (int, int ,int, int, int, int);

void do_V (void)
  {
  V = ((~leftop >> 31) && ( rightop >> 31) && ( result >> 31)) ||
      (( leftop >> 31) && (~rightop >> 31) && (~result >> 31));
  }

void do_C (void)
  {
  incarries = leftop ^ rightop ^ result;
  C = ((unsigned int) incarries >>      31) ^ V;
  outcarries = (C << 31) | (incarries >> 1);
  }
   
void add (void)
  {
  operator_char = '+';
  result = leftop + rightop;

  V = ((~leftop >> 31) && (~rightop >> 31) && ( result >> 31)) ||
      (( leftop >> 31) && ( rightop >> 31) && (~result >> 31));
  do_C();
  }

void subc2 (void)
  {
  operator_char = '+';
  result = leftop + ~rightop+1;
  do_V (); rightop = ~rightop; do_C ();
  }

void sub (void)
  {
  operator_char = '-';
  result = leftop + ~rightop +1;
  do_V (); do_C ();
  }
