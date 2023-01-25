/**************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble        */
/* 20/12/2007                                                 */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

unsigned int number_of_bits;
unsigned int leftop, rightop, result, carries, shift;
unsigned int incarries, outcarries;

int C, V, Z, N;

int left,right,res;
unsigned int uleft,uright,ures;

int detail = 0;
int no_shift_leftop = 0;
int no_shift_rightop = 0;

func *ptfunction;
func *ptdisplay;

char operator_char;

void exit_error (char *message)
  {
  fprintf (stderr,"Fatal error : %s\n",message);
  exit (1);
  }

void usage (char *message)
  {
  fprintf (stderr, "Error : %s", message);
  
  fprintf (stderr, "Usage                  : operation number_of_bits leftop rightop\n");
  fprintf (stderr, "Operation may be       : add, sub, subc2, or, xor, lsr, asr, lsl,  ror, rol, msk1, msk2\n");
  fprintf (stderr, "                       : addsc, subsc, subc2sc for carry/borrow details\n");
  fprintf (stderr, "Operands syntax : operand  or /operand or -operand\n");
  fprintf (stderr, "Operand formats : dec_digits  or 0xhexa_digits or 0bbin_digits\n");
  fprintf (stderr,"Example : ./and 4 0b0011 0xd computes 4 AND_bit_by_bit 13 on 4 bits\n");
  exit (1);
  }

/******************************************************************/
/* Shift left before and shift right after computing              */
/* This keeps ZNCV ok                                             */
/******************************************************************/

void Lshift ()
  {
  shift = 32 - number_of_bits;
  if (! no_shift_leftop) leftop  <<= shift;
  if (! no_shift_rightop) rightop  <<= shift;
  }

void Rshift ()
  {
  shift = 32 - number_of_bits;
  
  left = (int) leftop >> shift;
  right = (int) rightop  >> shift;
  res = (int) result >> shift;

  uleft = (unsigned int) leftop >> shift;
  uright = (unsigned int) rightop  >> shift;
  ures = (unsigned int) result >> shift;
  }

/*******************************************************************/
/* C limitation : 1 << x value not defined for x >= size in bits   */
/* In this case, this function should return 0                     */
/*******************************************************************/

unsigned int one_lsl_x (unsigned int x)
  {
  /* computes  (x < number_of_bits) << x */
  unsigned int x_less_than_nb_bits = 
         (unsigned int) (x - number_of_bits) >> (SIZE_INT_IN_BITS - 1);
  return  x_less_than_nb_bits << x;
  }

