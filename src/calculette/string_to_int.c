/***************************************************************/
/* Author : Philippe WAILLE     UFR IMAG/ UJF Grenoble         */
/* 20/12/2007                                                  */
/* 12/02/20908 : ajout des opérateurs / et - sur les opérandes */
/***************************************************************/

#include <string.h>
#include "string_to_int.h"
#include "global.h"
#include "sprint_bin.h"

/******************************************************************/
/* ask for and read a string in readres                           */
/******************************************************************/

void get_string (FILE *stream, char *readres, char *message_print)
  {
  fprintf (stderr,"%s",message_print);
  fscanf (stream,"%s",readres);
  }


/********************************************************************/
/* Convert binary string to integer without checking for overflow   */
/********************************************************************/

int binary_to_int (const char *string, unsigned int *readres) 
  {
  int ok = 1;
  *readres = 0;
  while (*string != 0)
    {
    if ((*string != '0') && (*string != '1'))
       {
       ok = 0;
       usage ("%c is not a binary digit\n");
       break;
       }
    *readres <<= 1;
    *readres += *string - '0';
    string++;
    }
  return (ok);
  }

/**********************************************************************/
/* Removes either 0b or 0x prefix, spaces and leading zeros           */
/**********************************************************************/

char *strip (char *string)
  {
  char *c = string;
  while ((*c == '0') || (*c == 'b') ||( *c == 'x') || 
         (*c == ' ') || (*c == '\t'))
    c++;
  return c;
  }

/***********************************************************************/
/* convert ABCDEF to  abcdef and X to x                                */
/***********************************************************************/

void tolowercase (char * c)
  {
  while (*c != 0)
    {
    if ( (*c>= 'A') && (*c <= 'F')) *c = *c + 'a'-'A';
    if (*c == 'X') *c ='x';
    c++;
    }
  }

/**********************************************************************/
/* Convert string to integer value                                    */
/**********************************************************************/

void do_string_to_int (char *string, unsigned int *value,
                    char *error_message)
  {
  char c[35];
  int ok;
  int v;
  tolowercase(string);
  
  /* Binary or hexadecimal string                                       */
  /* Performs string1 -> int -> truncate -> string2                     */
  /* After removing prefix and leading zeros                            */
  /* string1 != string2 means integer too big for the number of bits    */
  
  if ((string [0] == '0') && (string[1] == 'x'))
    {
    ok = sscanf (string,"%x",value);
    truncate (value);
    sprintf (c,"%x",*value);
    if (ok == 1)
      {
      ok = !strcmp (strip(string),strip(c));
      }
    }
  else if ((string [0] == '0') && (string[1] == 'b'))
    {
    ok = binary_to_int (string+2,value);
    truncate (value);
    sprint_bin(c,*value, 32,0);
    if (ok == 1)
      {
      ok = !strcmp (strip(string),strip(c));
      }
    }
  else
    {
    /* neither prefix nor [a..f] allowed */
    ok = sscanf (string,"%d",value) ;
    if (strchr (string,'x') != NULL) ok=0;
    if (strchr (string,'a') != NULL) ok=0;
    if (strchr (string,'b') != NULL) ok=0;
    if (strchr (string,'c') != NULL) ok=0;
    if (strchr (string,'d') != NULL) ok=0;
    if (strchr (string,'e') != NULL) ok=0;
    if (strchr (string,'f') != NULL) ok=0;
    v = *value;
    v = ((unsigned int) v << (32 -number_of_bits)) >> (32 - number_of_bits);
    if (v != *value) ok = 0;
    /*
    if ((!strcmp (gargv[0],"lsr")) ||
        (!strcmp (gargv[0],"asr")) ||
        (!strcmp (gargv[0],"lsl")) ||
        (!strcmp (gargv[0],"rol")) ||
        (!strcmp (gargv[0],"ror")))
      if (v < 0) ok = 0;
    */
    }
  if (!ok) exit_error (error_message);
  }

void string_to_int (char *string, unsigned int *value,
                    char *error_message)
  {
  /* handle negative prefix (-) */
  if (*string == '-') 
    {
    do_string_to_int (string+1, value, error_message);
    if (*value > (1 << (number_of_bits - 1)))
      exit_error (error_message);
    else
      *value = - *value;
    return;
    }
  /* handle not prefix (/) */
  else if (*string == '/')
    {
    do_string_to_int (string+1, value, error_message);
    *value = ~ *value;
    truncate(value);
    }
  else
    do_string_to_int (string, value, error_message);
  }

