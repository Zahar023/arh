#include "myInterface.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

void
mySuperComputer ()
{
  int value;
  sc_memoryInit ();
  sc_regInit ();
  sc_memorySet (0, 16);
  sc_memorySet (1, 14);
  sc_memorySet (2, 12);
  sc_memorySet (3, 10);
  sc_memorySet (4, 8);
  sc_memorySet (5, 6);

  for (int i = 0; i < 6; ++i)
    {
      sc_memoryGet (i, &value);
      printf ("RAM [ %d ] : %d\n", i, value);
    }

  sc_memorySave ("savefile.bin");
  printf ("RAM was saved\n");
  sc_memorySet (1, 99);
  sc_memoryGet (1, &value);
  printf ("RAM [1] : %d\n", value);
  sc_memoryLoad ("savefile.bin");
  printf ("RAM was loaded\n");
  for (int i = 0; i < 6; ++i)
    {
      sc_memoryGet (i, &value);
      printf ("RAM [ %d ] : %d\n", i, value);
    }

  sc_regSet (DIVISION_ERROR_BY_ZERO, 1);
  sc_regSet (OVERFLOW, 1);
  sc_regSet (INVALID_COMMAND, 1);

  sc_regGet (OVERFLOW, &value);
  printf ("[FLAG] OVERFLOW: %d\n", value);
  sc_regGet (DIVISION_ERROR_BY_ZERO, &value);
  printf ("[FLAG] DIVISION_ERROR_BY_ZERO: %d\n", value);
  sc_regGet (OUT_OF_MEMORY, &value);
  printf ("[FLAG] OUT_OF_MEMORY: %d\n", value);
  sc_regGet (IGNORING_CLOCK_PULSES, &value);
  printf ("[FLAG] IGNORING_CLOCK_PULSES: %d\n", value);
  sc_regGet (INVALID_COMMAND, &value);
  printf ("[FLAG] INVALID_COMMAND: %d\n", value);

  sc_commandEncode (65, 127, &value);
  printf ("Value: %d\n", value);
  int command = 0;
  int operand = 0;
  sc_commandDecode (value, &command, &operand);
  printf ("Command: %d  Operand: %d\n", command, operand);
}

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
  mySuperComputer ();
  //	myTerm();
  // srand (time (NULL));

  return 0;
}