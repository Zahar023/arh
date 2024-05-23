#include "mySimpleComputer.h"

short int memory_arr[N];
char flag = 0;
short currMemCell;

int
sc_memoryInit ()
{
  currMemCell = 0;
  for (int i = 0; i < N; i++)
    memory_arr[i] = 0;
  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (0 > address || address > 99)
    {
      flag = 1;
      return 1;
    }
  memory_arr[address] = value;
  return 0;
}

int
sc_memoryGet (int address, int *value)
{
  if (0 > address || address > 99)
    {
      flag = 1;
      return -1;
    }
  *value = memory_arr[address];
  return 0;
}

int
sc_memorySave (char *filename)
{
  FILE *out = fopen (filename, "wb");
  if (out == NULL)
    return 1;
  fwrite (memory_arr, sizeof (memory_arr), 1, out);
  fclose (out);
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  FILE *in = fopen (filename, "rb");
  if (in == NULL)
    return 1;
  fread (memory_arr, sizeof (memory_arr), 1, in);
  fclose (in);
  return 0;
}

int
sc_regInit ()
{
  flag = 0;
  return 0;
}

int
sc_regSet (int _register, int value)
{
  if (_register < 0 || _register > 4)
    {
      write (1, "Error. Wrong _register\n", 24);
      return -1;
    }
  if (value < 0 || value > 1)
    {
      write (1, "Error. Wrong Value\n", 19);
      return -2;
    }

  if (value == 1)
    {
      flag = flag | (1 << _register);
    }
  else
    {
      flag = flag & ~(1 << _register);
    }
  return 0;
}

int
sc_regGet (int _register, int *value)
{
  if (_register < 0 || _register > 4)
    {
      return 1;
    }
  if (flag & (1 << _register))
    {
      *value = 1;
    }
  else
    {
      *value = 0;
    }
  return 0;
}

int
sc_commandEncode (int command, int operand, int *value)
{

  if (!((command >= 0x10 && command <= 0x11)
        || (command >= 0x20 && command <= 0x21)
        || (command >= 0x30 && command <= 0x33)
        || (command >= 0x40 && command <= 0x43)
        || (command >= 0x51 && command <= 0x76)))
    {
      write (STDOUT_FILENO, "Error\n", 6);
      return -1;
    }
  if (operand < 0 || operand > 127)
    {
      write (STDOUT_FILENO, "Error\n", 6);
      return -2;
    }

  *value = 0;
  *value = *value | operand;
  *value = *value | (command << 7);
  return 0;
}

int
sc_commandDecode (int value, int *command, int *operand)
{
  *operand = 0;
  *command = 0;

  if (value & 0x4000)
    return 1;

  *command = (value & 0x3F80) >> 7; // 16256
  *operand = (value & 0x7F);        // 127

  return 0;
}
