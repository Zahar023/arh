#include "myTerm.h"
#include <unistd.h> // for write and dup2

int
mt_clrscr ()
{
  write (1, "\E[H\E[2J", 7);
  return 0;
}

int
set_default_color ()
{
  write (1, "\033[0m", 4);
  return 0;
}

int
mt_gotoXY (int _x, int _y)
{
  int count_rows, count_columns;

  if (mt_getscreensize (&count_rows, &count_columns) == -1)
    {
      return -1;
    }

  if ((_x > count_columns) || (_x <= 0) || (_y > count_rows) || (_y <= 0))
    {
      return -1;
    }

  char buf[16];
  int len = snprintf (buf, 16, "\033[%d;%dH", _y, _x);
  write (1, buf, len);

  return 0;
}

int
mt_getscreensize (int *_rows, int *_columns)
{
  struct winsize window_size;

  if (ioctl (1, TIOCGWINSZ, &window_size))
    {
      return -1;
    }

  *_rows = window_size.ws_row;
  *_columns = window_size.ws_col;

  return 0;
}

int
mt_setfgcolor (enum colors color)
{
  char buf[16];
  int len = snprintf (buf, 16, "\033[38;5;%dm", color);
  write (1, buf, len);
  return 0;
}

int
mt_setbgcolor (enum colors color)
{
  char buf[16];
  int len = snprintf (buf, 16, "\033[48;5;%dm", color);
  write (1, buf, len);
  return 0;
}
