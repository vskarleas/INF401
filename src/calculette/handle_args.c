/**************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble        */
/* 20/12/2007                                                 */
/*                                                            */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "handle_args.h"
#include "global.h"
#include "bit_bit.h"
#include "add_sub.h"
#include "string_to_int.h"
#include "sprint_bin.h"
#include "display.h"

static char operand [40];

func *check_name (char *name)
  {
  set_margin(10);
  ptdisplay = &show_add;
  if (!strcmp(name,"add"))    {return &add;}
  if (!strcmp(name,"addsc"))  { detail = 1; return &add;}
  if (!strcmp(name,"sub"))    {return &sub;}
  if (!strcmp(name,"subsc"))  { detail = 1; return &sub;}
  if (!strcmp(name,"subc2"))  { return &subc2;}
  if (!strcmp(name,"subc2sc")){ detail = 1; return &subc2;}
  set_margin(8);
  ptdisplay = &show_shift;
  if (!strcmp(name,"lsr"))    {no_shift_rightop=1;return &lsr;}
  if (!strcmp(name,"asr"))    {no_shift_rightop=1;return &asr;}
  if (!strcmp(name,"lsl"))    {no_shift_rightop=1;return &lsl;}
  if (!strcmp(name,"ror"))    {no_shift_rightop=1;return &ror;}
  if (!strcmp(name,"rol"))    {no_shift_rightop=1;return &rol;}
  ptdisplay = &show_log;
  set_margin(10);
  if (!strcmp(name,"and"))    {return &and;}
  if (!strcmp(name,"or"))     {return &or;}
  if (!strcmp(name,"xor"))    {return &xor;}
  if (!strcmp(name,"not"))    { singleop = 1; return &not;}
  ptdisplay = &show_msk1;
  if (!strcmp(name,"msk1"))    
     {no_shift_leftop=1; no_shift_rightop=1; return &msk1;}
  ptdisplay = &show_msk2;
  if (!strcmp(name,"msk2"))
     {no_shift_leftop=1; no_shift_rightop=1; return &msk2;}
    else
      {
      usage ("Unknown operator\n");
      return NULL;
      }
  }

void handle_args (int argc, char *argv[])
  {
  char *ask_msg, *error_msg, *string;
  char *pchar;
  
  /* Command line argv[0] selects operation */
  
  /* Remove directory path prefix */
  pchar= argv[0];
  while (*pchar!= 0)
    {
    if (*pchar== '/') argv[0] = pchar+1;
    pchar++;
    }
  detail = 0;

  ptfunction = check_name(argv[0]);

  if (argc > 4) usage ("Too much arguments\n");
  
  /****************************************************************/
  /* Get number_of_bits                                           */
  /****************************************************************/
  
  /* String_to_int uses number_of_bit for ANY string -> int conversion */
  /* On first call : argv[1] ->  number_of_bits itself !!!             */
  /*                 uses default max bits                             */
  
  number_of_bits = SIZE_INT_IN_BITS;
  
  if (argc == 1)
    {
    ask_msg = "Get the number of bits\n";
    get_string (stdin, operand, ask_msg); 
    string = operand;
    }
  else
    {
    string= argv[1];
    }
  error_msg = "Invalid number of bits\n";
  do_string_to_int (string, &number_of_bits,error_msg);
  
  if ((number_of_bits < 2) || (number_of_bits > 32))
     usage ("Number of bits should belong to [2 .. 32]\n");
  
  /***************************************************************/
  /* Get left operand                                            */
  /***************************************************************/
  
  error_msg = "Invalid left operand\n";
  if (argc < 3)
    {
    ask_msg = "Get left operand\n";
    get_string (stdin, operand, ask_msg);
    string = operand;
    }
  else
    {
    string = argv[2];
    }
  string_to_int (string, &leftop, error_msg);
  
  /***************************************************************/
  /* Get right operand                                           */
  /***************************************************************/
  
  error_msg = "Invalid right operand\n";
  if (argc < 4)
    {
    ask_msg = "Get right operand\n";
    get_string (stdin, operand, ask_msg);
    string = operand;
    }
  else
    {
    string = argv[3];
    }
  string_to_int (string, &rightop, error_msg);
  }
