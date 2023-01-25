/**************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble        */
/* 20/12/2007                                                 */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "display.h"
#include "sprint_bin.h"
#include "global.h"

static char format[30] = " 0x%8x --> %10u or %+11d\n";
int singleop = 0;

char s[40];
char *ps;

/***************************************************************/
/* printf left margin with str suffix                          */
/***************************************************************/

void printleft (char *str) 
  { 
  printf ("%s%s",margin+strlen(str),str); 
  ps=s; 
  }

/*****************************************************************/
/* Display a single operand or result                            */
/* binary,  hexa, unsigned dec , signed dec                      */
/*****************************************************************/

void show_operand (char *s1, char *s2, 
                   int op1, unsigned int op2, int op3)
  {
  printf ("%s",s1);
  truncate(&op2);
  print_bin (op1);
  printf ("%s",s2);
  printf (format, op2, op2, op3);
  }

/*****************************************************************/
/* Display result with Z and N flags                             */
/*****************************************************************/

void show_res ()
  {
  char left [10];
  sprintf (left, "Z=%1d N=%1d->",(res==0),(res <0));
  printleft(left);
  show_operand(""," =     : ", result, ures,res);
  }

/*****************************************************************/
/* Display not, and,or, xor operations                           */
/*****************************************************************/

void show_log (void)
  {
  printf ("                           if natural     if signed\n\n");
  if (! singleop)
     show_operand(margin,  "left   : ", leftop, uleft, left);
  printf ("%c",operator_char);
  show_operand(margin+1,
                singleop ? "       : " : "right  : ", 
		                       rightop, uright, right);
  printf ("%s", margin);
  print_string(lineres);
  printf ("\n");
  show_res ();
  }

/*******************************************************************/
/* Display shift and rotation operations                           */
/*******************************************************************/

void show_shift (void)
  {
  int i;

  void flushs (char *str)  { *ps = 0; print_string (s);printf ("%s\n",str);}

  void fill (int n, char c)
    {
    int i;
    for (i=0; i< n;i++) *ps++ = c;
    }

  void line (char *l, char before, char first, char *r)
    {
    printleft (l);
    if (before)
      {
      fill (rightop,first); 
      fill (number_of_bits - rightop,'_');
      }
    else
      {
      fill (number_of_bits - rightop,'_');
      fill (rightop,first); 
      }
    flushs (r);
    }


  printf ("                           if natural     if signed\n\n");

  
  switch (operator_char) 
    {
    case 'l' :  show_operand(margin,  "       : ", leftop, uleft, left);
                line ("<-",1,'-',"-- 0");
                line ("<-",0,'-',"-- 0");
		break;
    case 'r':   show_operand(margin,  "       : ", leftop, uleft, left);
                line ("0 --",0,'-',"->");
                line ("0 --",1,'-',"->");
		break;
    case 'a':   printleft ("s=");
                show_operand("",  "       : ", leftop, uleft, left);
                line ("s --",0,'-',"->");
                line ("s --",1,'s',"->");
		break;
    case 'o':   show_operand(margin,  "       : ", leftop, uleft, left);
                line ("---",0,'#',"---");
                printleft ("^   ");
                for (i=0;i< number_of_bits;i++) s[i] = ' ';
		s[i] = 0; strcat (s,"   v");
                print_string(s); printf ("\n");
                line ("---",1,'#',"---");
		break;
    case 'O':   show_operand(margin,  "       : ", leftop, uleft, left);
                line ("---",1,'#',"---");
                printleft ("V   ");
                for (i=0;i< number_of_bits;i++) s[i] = ' ';
		s[i] = 0; strcat (s,"   ^");
                print_string(s); printf ("\n");
                line ("---",0,'#',"---");
		break;
    }
    show_operand(margin,  "       : ", result, ures, res);
  }

#define DIFF_SIZE (SIZE_INT_IN_BITS-number_of_bits)

void show_msk2 (void)
  {
  int diff,nbl;
  unsigned int tmp1,tmp2;
  char format[10];
  diff = leftop - rightop;
  nbl = number_of_bits - 1 - diff;
  printf ("                           if natural     if signed\n\n");
  printleft ("~ 0 : ");
  tmp1 = ~0;
  show_operand("","        :", tmp1, tmp1, tmp1);
  sprintf (format,">>%2d : ", nbl); printleft(format);
  tmp1 >>= (number_of_bits - 1 - diff);
  tmp2 = ~0;
  show_operand("","        :", tmp1,tmp1,tmp1);
  printleft("");print_string(lineres); printf ("\n");
  sprintf (format,"<<%2d : ", rightop); printleft(format);
  show_operand("","        :", result<< DIFF_SIZE, result, result);
  }

void show_msk1 (void)
  {
  unsigned int tmp;
  char format[10];
  printf ("                           if natural     if signed\n\n");
  sprintf (format,"1<<%2d ", leftop+1); printleft(format);
  tmp = one_lsl_x (leftop+1);
  show_operand("","        :", tmp << DIFF_SIZE,tmp,tmp);
  sprintf (format,"- 1<<%2d ", rightop); printleft(format);
  tmp = one_lsl_x (rightop);
  show_operand("","        :", tmp << DIFF_SIZE,tmp,tmp);
  printleft (""); print_string(lineres); printf ("\n");
  printleft ("= ");
  show_operand("","        :", result  << DIFF_SIZE, result, result);
  if (leftop+1 >= number_of_bits)
     {
     printf ("\n%sWarning : 1 << x with x >= number_of_bits is not defined in C. See one_lsl_x function in global.c\n",margin);
     }
  }


/*******************************************************************/
/* display add and sub operations                                  */
/*******************************************************************/

void do_detail_bit_add (int bit, int left, int right,
                        int cin, int result, int cout)
  {
  int somme = left+right+cin;
  printf (       "l + right + in_c :  %1d+%1d+%1d = %1d", 
          left, right, cin, somme);
  if (somme >= 2)
    printf (" (>=2) --> res = %1d (%1d -2), out_c = 1\n", 
              result, somme);
  else
    printf (" ( <2) --> res = %1d       , out_c = 0\n", result);

  }

void do_detail_bit_sub (int bit, int left, int right,
                        int cin, int result, int cout)
  {
  int somme = right+cin;
  printf (       "right + in_b : %1d+%1d = %1d", 
           right, cin, somme);
  if (somme > left)
    printf (" (>  l=%1d) --> res = %1d (%1d - %1d + 2), out_b = 1\n", 
              left, result, left, somme);
  else
    printf (" (<= l=%1d) --> res = %1d (%1d - %1d),     out_b = 0\n", 
              left, result, left, somme);
  }

void do_detail_bit (int bit)
  {
  int a, b, cin, r, cout;
  char format[10];
  a = ( uleft >> bit) & 1;
  b = (uright >> bit) & 1;
  r = ( ures >> bit) & 1;
  cin = (incarries >> bit) & 1;
  cout = (outcarries >> bit) & 1;
  sprintf (format, "col %2d  ", bit);
  printleft (format);
  if (operator_char == '+')
    do_detail_bit_add (bit, a,b,cin,r,cout);
  else
    do_detail_bit_sub (bit, a,b,cin,r,cout);
  }

void do_detail (void)
  {
  int bit;
  char format[10];
  sprintf (format,"%c -->",(operator_char == '+') ? 'C':'B');
  printleft (format);
  print_bin (outcarries);
  printf ("<-- %c1   (%s detail)\n", (operator_char == '+') ? 'c' : 'b',
          (operator_char == '+') ?  "out carries" : "out borrows");
  printf ("\n");
  incarries >>= shift;
  outcarries >>= shift;
  for (bit = 0;bit < number_of_bits; bit++) do_detail_bit (bit);
  }

void show_add (void)
  {
  char lefts [20];

  printf ("                           if natural     if signed\n\n");
  show_operand(margin,  "left   : ", leftop, uleft, left);

  strcpy (s,margin);
  s[strlen(s) - 1] = ' ';
  s[strlen(s) - 2] = operator_char;
  printleft(s);
  show_operand("",       "right  : ", rightop, uright, right);

  sprintf (lefts,"%c=%1d %s ",(operator_char == '+') ? 'C' : 'B', C,
                              V ? "!=" : "==");
  printleft (lefts); print_bin(incarries); 
                 printf ("< %1c0=%1d   (%s)\n",
		         (operator_char == '+') ? 'c' : 'b',
			 incarries & 1,
			 (operator_char == '+') ? "in carries" : "in borrows");

  sprintf (lefts,"V=%1d  ^ ", V );
  printleft (lefts);
  print_string(lineres);
  printf ("\n");

  show_res ();
  if (detail) do_detail();
  }


