#ifndef GLOBAL_H
#define GLOBAL_H

#define SIZE_INT_IN_BITS  (8*sizeof(int))

typedef void func ();

extern unsigned int number_of_bits;
extern unsigned int leftop, rightop, result, carries, shift;
extern unsigned int incarries, outcarries;

extern int C, V, Z, N;


extern int left,right,res;
extern unsigned int uleft,uright,ures;

extern int detail;
extern int no_shift_leftop;
extern int no_shift_rightop;

extern func *ptfunction;
extern func *ptdisplay;

extern char operator_char;

void exit_error (char *message);
void usage (char *message);
void Lshift ();
void Rshift ();
unsigned int one_lsl_x (unsigned int x);

#endif

