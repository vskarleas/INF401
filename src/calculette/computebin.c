/***************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble         */
/* 20/12/2007                                                  */
/***************************************************************/

#include <stdio.h>
#include "handle_args.h"
#include "global.h"
#include "sprint_bin.h"

void do_job (void)
  {
  bits_numbers ();
  Lshift ();
  (*ptfunction)();
  Rshift ();
  (*ptdisplay) ();
  }

int main (int argc, char *argv[])
  {
  handle_args (argc,argv);
  do_job();
  return (0);
  }
