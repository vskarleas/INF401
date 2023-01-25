#ifndef DISPMAY_H
#define DISPMAY_H

extern int singleop;

void show_operand (char *s1, char *s2, 
                   int op1, unsigned int op2, int op3);
void show_log (void);
void show_shift (void);
void show_add (void);
void show_msk1 (void);
void show_msk2 (void);
#endif

