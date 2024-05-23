
#include "myBigChars.h"
#include "myInterface.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

extern int instruction_counter;

void
testBIGCHARS ()
{
  mt_clrscr ();
  bc_printBigChar (big_chars[8], 5, 10, 2, 1);
  mt_gotoXY (1, 24);
}

int
main ()
{
  // mySuperComputer();
  // myTerm();

  testBIGCHARS ();

  return 0;
}
