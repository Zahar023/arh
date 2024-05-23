#include "myReadKey.h"
#include "mySimpleComputer.h"

int
main ()
{
  rk_myTermSave ();
  enum keys key;
  int value;
  sc_memorySet (0, 5);
  sc_memoryGet (0, &value);
  printf ("address[0] =  %d\n", value);
  printf ("Enter S_KEY\n");
  rk_readKey (&key);
  if (key == S_KEY)
    sc_memorySave ("savefile.bin");
  printf ("Successful save\n");
  sc_memorySet (0, 6);
  sc_memoryGet (0, &value);
  printf ("address[0] =  %d\n", value);
  printf ("Value was changed! Enter L_KEY for load previous setup\n");
  rk_readKey (&key);
  if (key == L_KEY)
    sc_memoryLoad ("savefile.bin");
  sc_memoryGet (0, &value);
  printf ("address[0] =  %d\n", value);
  key = ESC_KEY;
  return 0;
}