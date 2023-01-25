/***************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble         */
/* 20/12/2007                                                  */
/***************************************************************/


#include "bit_bit.h"
#include "global.h"

/*****************************************************************/
/* bit  bit operators                                            */
/*****************************************************************/

void not (void)
  {
  result = ~ rightop;
  operator_char = '~';
  }

void and (void)
  {
  result = leftop & rightop;
  operator_char = '&';
  }

void or (void)
  {
  result = leftop | rightop;
  operator_char = '|';
  }

void xor (void)
  {
  result = leftop ^ rightop;
  operator_char = '^';
  }

void check_nb_shift (int x)
  {
  if (x >= number_of_bits) exit_error ("Shift number >= Number of bits\n");
  }

void lsr (void)
  {
  operator_char = 'r';
  check_nb_shift (rightop);
  result = (unsigned int) leftop >> rightop;
  }

void asr (void) 
  {
  operator_char = 'a';
  check_nb_shift (rightop);
  result = (int) leftop >> rightop;
  }

void lsl (void)
  {
  operator_char = 'l';
  check_nb_shift (rightop);
  result = (unsigned int) leftop << rightop;
  }

void ror (void)
  {
  int nb_shift;
  int one, two;
  check_nb_shift (rightop);
  operator_char = 'o';
  nb_shift = rightop;
  one = (unsigned int) leftop >> nb_shift; 
  two =   leftop << (number_of_bits - nb_shift);
  result = one | two;
  }

void rol (void)
  {
  int nb_shift;
  int one, two;
  check_nb_shift (rightop);
  operator_char = 'O';
  nb_shift = rightop;
  one = (unsigned int) leftop >> (number_of_bits -nb_shift); 
  two =   (leftop << nb_shift);
  result = one | two;
  }

/*******************************************************************/
/* bit mask computation                                            */
/*******************************************************************/

void msk2 (void)
  {
  int nbl;
  check_nb_shift (leftop);
  check_nb_shift (rightop);
  if (rightop > leftop) exit_error ("right bit number > left bit number\n");
  nbl = SIZE_INT_IN_BITS- 1 - leftop;
  result = ((unsigned int) ~0) >> (rightop + nbl);
  result <<= rightop;
  }

void msk1 (void)
  {
  check_nb_shift (leftop);
  check_nb_shift (rightop);
  if (rightop > leftop) exit_error ("right bit number > left bit number");
  result = one_lsl_x (leftop+1) - one_lsl_x (rightop);
  }

