#ifndef MYTERM_H
#define MYTERM_H
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h> // for write and dup2

enum colors
{
  RED = 196,
  PEACH = 203,
  GREEN = 10,
  SOFT_GREEN = 192,
  BLUE = 20,
  BLACK = 16,
  GRAY = 240,
  WHITE = 15,
  DEFAULT = 0
};

int mt_clrscr ();
int mt_gotoXY (int _x, int _y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
int set_default_color ();

#endif