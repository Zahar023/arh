#include "myBigChars.h"
#include "myInterface.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

bool on = 1;

int
main ()
{
  rk_myTermSave ();
  sc_memoryInit ();
  int rows, cols;
  for (int i = 0; i < N; ++i)
    sc_memorySet (i, i + 1);
  // sc_memorySet (0, 5);
  mt_getscreensize (&rows, &cols);
  if (rows < 24 || cols < 24)
    return -1;
  ui_initial ();
  enum keys key;

  do
    {
      ui_update ();
      rk_readKey (&key);
      switch (key)
        {
        case UP_KEY:
          (instruction_counter <= 9)
              ? (instruction_counter = 90 + instruction_counter)
              : (instruction_counter -= 10);
          break;
        case RIGHT_KEY:
          (!((instruction_counter + 1) % 10)) ? (instruction_counter -= 9)
                                              : (instruction_counter += 1);
          break;
        case DOWN_KEY:
          (instruction_counter >= 90)
              ? (instruction_counter = instruction_counter - 90)
              : (instruction_counter += 10);
          break;
        case LEFT_KEY:
          (!(instruction_counter % 10)) ? (instruction_counter += 9)
                                        : (instruction_counter -= 1);
          break;

        case L_KEY:
          sc_memoryLoad ("savefile.bin");
          break;
        case S_KEY:
          sc_memorySave ("savefile.bin");
          break;

        // case R_KEY:     break ;
        // case T_KEY:     break ;
        case I_KEY:
          sc_memoryInit ();
          instruction_counter = 0;
          currMemCell = 0;
          break;

        // case F5_KEY:    break ;
        case F6_KEY:
          ui_Counter ();
          break;

        case ENTER_KEY:
          ui_setValue ();
          ui_update ();
          break;
        case ESC_KEY:
          on = 0;
          break;
        }
    }
  while (on);
  mt_gotoXY (1, 24);
  return 0;
}
