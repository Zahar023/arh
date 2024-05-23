#include "myInterface.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "myTerm.h"

int instruction_counter;

char buffer[512];
short ind;

int
drawingBoxes ()
{
  if (bc_box (1, 1, 61, 12)) // Окно Memory
    return -1;
  if (bc_box (62, 1, 22, 3)) // Окно accumulator
    return -1;
  if (bc_box (62, 4, 22, 3)) // Окно instructionCounter
    return -1;
  if (bc_box (62, 7, 22, 3)) // Окно Operation
    return -1;
  if (bc_box (62, 10, 22, 3)) // Окно Flags
    return -1;
  if (bc_box (1, 13, 52, 10)) // Окно BigChars
    return -1;
  if (bc_box (53, 13, 31, 10)) // Окно Keys
    return -1;

  return 0;
}

int
drawing_texts ()
{
  mt_gotoXY (30, 1);
  write (1, " Memory ", 8);

  mt_gotoXY (66, 1);
  write (1, " accumulator ", 13);

  mt_gotoXY (63, 4);
  write (1, " instructionCounter ", 21);

  mt_gotoXY (68, 7);
  write (1, " Operation ", 11);

  mt_gotoXY (68, 10);
  write (1, " Flags ", 7);

  mt_gotoXY (54, 13);
  write (1, " Keys: ", 7);

  /* HotKeys */
  char *hot_keys[7] = { (char *)"l  - load",
                        (char *)"s  - save",
                        (char *)"r  - run",
                        (char *)"t  - step",
                        (char *)"i  - reset",
                        (char *)"F5 - accumulator",
                        (char *)"F6 - instructionCounter" };

  for (int i = 0; i < 7; ++i)
    {
      mt_gotoXY (54, i + 14);
      write (1, hot_keys[i], strlen (hot_keys[i]));
    }

  mt_gotoXY (1, 24);

  return 0;
}

int
drawingBigChars ()
{
  // int tmp = memory_arr[instruction_counter];
  int value, command, operand;
  sc_memoryGet (instruction_counter, &value);
  if (sc_memoryGet (instruction_counter, &value) < 0)
    {
      return -1; // обработка ошибки чтения из памяти
    }
  if (sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    {
      return -2; // обработка ошибки декодирования команды
    }

  if (!(value & 0x4000))
    {
      ind = 16;
      bc_printBigChar (big_chars[ind], 2, 14, GREEN, 0);
    }

  else
    {
      ind = 17;
      bc_printBigChar (big_chars[ind], 2, 14, GREEN, 0);
    }

  int ch;
  for (int i = 0; i < 4; ++i)
    {
      switch (i)
        {
        case 0:
          ch = (command >> 4) & 0xF;
          break;
        case 1:
          ch = (command)&0xF;
          break;
        case 2:
          ch = (operand >> 4) & 0xF;
          break;
        case 3:
          ch = (operand)&0xF;
          break;
        }
      bc_printBigChar (big_chars[ch], 2 + 8 * (i + 1) + 2 * (i + 1), 14, GREEN,
                       0);
    }

  return 0;
}

int
drawing_memory ()
{
  int value, command, operand;
  char buf[6];
  for (int i = 0; i < 10; ++i)
    {
      for (int j = 0; j < 10; ++j)
        {
          int address = i * 10 + j;
          if (sc_memoryGet (address, &value) < 0)
            {
              return -1; // обработка ошибки чтения из памяти
            }
          if (sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
            {
              return -2; // обработка ошибки декодирования команды
            }
          mt_gotoXY (2 + (5 * j + j), 2 + i);
          if (instruction_counter == address)
            {
              mt_setbgcolor (GREEN);
            }
          snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+',
                    command, operand);
          write (STDOUT_FILENO, buf, strlen (buf));
          set_default_color ();
        }
    }
  return 0;
}

int
drawing_OP ()
{
  int value;
  int command;
  int operand;
  sc_memoryGet (instruction_counter, &value);
  mt_gotoXY (66, 8);
  char buf[32];
  if (sc_commandDecode (value, &command, &operand) > 0)
    {
      sc_regSet (4, 1);
      sprintf (buf, "Invalid command");
      write (STDOUT_FILENO, buf, strlen (buf));
      return -1;
    }
  mt_gotoXY (65, 8);
  sprintf (buf, "                 ");
  write (STDOUT_FILENO, buf, strlen (buf));
  mt_gotoXY (68, 8);
  sprintf (buf, " +%02X : %02X", command, operand);

  write (STDOUT_FILENO, buf, strlen (buf));
  return 0;
}

int
drawing_flags ()
{
  char buffff[5];
  char tmp[] = { 'O', 'Z', 'M', 'C', 'I' };
  for (int i = 0; i < REGISTER_SIZE; ++i)
    {
      int value, value2;
      if (sc_regGet (i, &value))
        return -1;
      sc_memoryGet (instruction_counter, &value2);
      mt_gotoXY (68 + (i * 2), 11);

      if (value && (value2 & 0x4000))
        {
          mt_setfgcolor (RED);
          write (STDOUT_FILENO, &tmp[i], 1);
        }
      else
        {
          mt_setfgcolor (GRAY);
          write (STDOUT_FILENO, &tmp[i], 1);
        }

      set_default_color ();
    }

  return 0;
}

/*
int
a()
{
  char flags[] = { 'O', 'Z', 'M', 'P', 'C' };

  for (int i = 0; i < REGISTER_SIZE; ++i)
    {
      int value;

      sc_regGet (i, &value);

      mt_gotoXY (69 + (i * 2), 11);
      char flag = flags[i];
      write (STDOUT_FILENO, &flag, 1);
    }

Код этой функции делает не то, что требуется. Нужно вывести флаги (если они
установлены) и на этом остановиться. При чем здесь вывод instructionCounter?
Второй момент. InstructionCounter - это самостоятельный регистр, который будет
изменяться только в процессе выполнения загруженной в память SimpleComputer
программы. Сейчас он содержит 0. Дальше - в следующем блоке "Operation" должен
выводиться результат декодирования ячейки памяти, адрес которой указан в
instructionCounter. Если декодирование невозможно, то должен быть установлен
флаг "Ошибка декодирования команды"




  mt_gotoXY (69, 8);

  char buff[32];
  sprintf (buff, "%04X : %04X", command, operand);
  write (STDOUT_FILENO, buff, 14);



  return 0;
}
*/

int
ui_Counter ()
{
  char buffer[32];
  write (1, "\033[2K", 4);
  mt_gotoXY (1, 24);
  write (STDOUT_FILENO, "Enter instruction_counter: ", 28);
  fgets (buffer, 32, stdin);
  instruction_counter = atoi (buffer);
  if (instruction_counter < 0 || instruction_counter > 99)
    {
      instruction_counter = 0;
      mt_clrscr ();
      write (STDOUT_FILENO, "\033[38;5;196mError\n", 17);
      return 1;
    }
  drawing_IC ();
  return 0;
}

int
drawing_IC ()
{
  mt_gotoXY (70, 5);
  char buff[32];
  sprintf (buff, "+%04d", instruction_counter);
  write (STDOUT_FILENO, buff, 5);
  return 0;
}

int
ui_initial ()
{
  mt_clrscr ();
  mt_gotoXY (70, 2);
  write (STDOUT_FILENO, "+0000", 5);
  instruction_counter = 0;
  mt_gotoXY (70, 5);
  write (STDOUT_FILENO, "+0000", 5);
  if (drawingBoxes ())
    return -1;
  if (drawing_texts ())
    return -1;
  if (drawing_memory ())
    return -1;
  mt_gotoXY (1, 24);

  return 0;
}

int
ui_update ()
{

  if (drawingBoxes ())
    return -1;
  if (drawing_texts ())
    return -1;
  if (drawing_memory ())
    return -1;
  if (drawing_flags ())
    return -1;
  if (drawingBigChars ())
    return -1;

  drawing_OP ();

  mt_gotoXY (1, 24);
  write (1, "\033[2K", 4);
  write (1, "Input: ", 7);

  return 0;
}

int
ui_setValue ()
{

  char buffer[10];
  fgets (buffer, 10, stdin);
  mt_gotoXY (8, 24);
  write (1, "\033[2K", 4);

  if (buffer[strlen (buffer) - 1] != '\n')
    clearBuffIn ();

  if (!checkCorrectInput (buffer))
    {
      mt_gotoXY (1, 24);
      ui_messageOutput ((char *)"Invalid input", RED);
      return -1;
    }

  long int number;
  char *tmp;

  if (buffer[0] == '+')
    {
      number = strtol (&buffer[1], &tmp, 16);
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The command value must not exceed 14 bits (0x3FFF)",
              RED);
          sleep (1);
          return -1;
        }
      sc_memorySet (instruction_counter, number);
    }
  else if (buffer[0] != '-')
    {
      number = strtol (buffer, &tmp, 16);
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The command value must not exceed 14 bits (0x3FFF)",
              RED);
          sleep (1);
          return -1;
        }
      sc_memorySet (instruction_counter, number);
    }
  else if (buffer[0] == '-')
    {
      number = strtol (&buffer[1], &tmp, 16);
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The value must not exceed 14 bits (0x3FFF)", RED);
          sleep (1);
          return -1;
        }
      number = number | 0x4000;

      sc_memorySet (instruction_counter, number);
    }

  return 0;
}

bool
checkCorrectInput (const char buffer[10])
{
  int i;
  if (buffer[0] == '+' || buffer[0] == '-')
    {
      if (strlen (buffer) == 2 || strlen (buffer) > 6)
        return false;
      i = 1;
    }
  else
    {
      i = 0;
      if (strlen (buffer) == 1 || strlen (buffer) > 5)
        return false;
    }
  for (i; i < strlen (buffer) - 1; ++i)
    if (!(isxdigit (buffer[i])))
      return false;

  return true;
}

int
ui_messageOutput (char *str, enum colors color)
{

  char buff[32];
  sprintf (buff, "\033[38;5;%dm%s\033[0m", color, str);
  write (STDOUT_FILENO, buff, 32);
  sleep (1.5);
  write (1, "\033[2K", 4);
  return 0;
}

int
clearBuffIn ()
{
  int c;
  do
    {
      c = getchar ();
    }
  while (c != '\n' && c != '\0');
  return 0;
}