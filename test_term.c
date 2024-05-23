#include "myInterface.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

void
myTerm ()
{
  mt_clrscr ();
  mt_gotoXY (4, 4);
  mt_setfgcolor (BLUE);
  printf ("Hello with blue color\n");
  mt_setbgcolor (WHITE);
  printf ("Goodbye with white background color\n");
  printf ("\033[0m");
}

int
main ()
{
  // mySuperComputer();
  myTerm ();
  // srand (time (NULL));

  return 0;
}