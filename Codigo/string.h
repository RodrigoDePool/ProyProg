
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

typedef struct _String   String;

/*Initializes and returns String struct from a file like this (# is the separator):

   3 --nstrings
   I'm sorry, you need to have the three parts if you wanna have a clue!#

   Everything was successfuly saved.#

   Enter the solution to the riddle#

 */
String *string_ini(char *path);

/* Frees a given string and all its members*/
void string_free(String *s);

/*Returns the number of strings in a struct, or -1 in case of error*/
int string_getNumber(String *s);

/*Returns the i-th string of  a struct NOT A COPY, or NULL when error*/
char * string_getString(String *s, int i);

/*Given a string like this:
   Hello, my name is $
   stupid dictador and $
   im stupid :D $@

   where sep = $ and finish = @,
   draws three strings in (in, bdc) starting at (row, col), each one a row lower
   than the other. Returns the row where the user should start writing again

   IF USING WITH STRING_INI, BE CAREFUL: YOUR FILE SHOULD BE LIKE THIS
     Hello, my name is $
     stupid dictador and $
     im stupid :D $@#
   IF YOU WANT TO PRINT:
    Hello, my name is
    stupid dictador and
    im stupid :D


 */
int string_drawLines(Interface *in, char *s, int row, int col, int bdc, char sep, char finish);
