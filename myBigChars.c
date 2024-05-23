#include "myBigChars.h"

unsigned int big_chars[][2] = {
  { 0xE7E7FFFF, 0xFFFFE7E7 }, // 0
  { 0x1CDC7C3C, 0xFFFF1C1C }, // 1
  { 0xFF07FFFF, 0xFFFFE0FF }, // 2
  { 0xFF07FFFF, 0xFFFF07FF }, // 3
  { 0xFFE7E7E7, 0x070707FF }, // 4
  { 0xFFE0FFFF, 0xFFFF07FF }, // 5
  { 0xFFE0FFFF, 0xFFFFE7FF }, // 6
  { 0x1C0EFFFE, 0x3838FE38 }, // 7
  { 0x7EE7FF7E, 0x7EFFE77E }, // 8
  { 0xFFE7FFFF, 0xFFFF07FF }, // 9
  { 0xFFE7FF7E, 0xE7E7E7FF }, // A
  { 0xFEE7FFFE, 0xFEFFE7FE }, // B
  { 0xE0E7FF7E, 0x7EFFE7E0 }, // C
  { 0xE7E7FFF8, 0xF8FFE7E7 }, // D
  { 0xFFE0FFFF, 0xFFFFE0FF }, // E
  { 0xFFE0FFFF, 0xE0E0E0FF }, // F
  { 0x7E180000, 0x00000018 }, // +
  { 0x7E000000, 0x00000000 }, // -
};

char buf[512];

int
bc_printA (char charr)
{
  sprintf (buf, "\033(0%c\033(B", charr);
  write (1, buf, strlen (buf));
  return 0;
}

int
bc_box (int x, int y, int width, int height)
{
  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if ((x <= 0) || (y <= 0) || (x + width - 1 > cols) || (y + height - 1 > rows)
      || (width <= 1) || (height <= 1))
    return -1;

  mt_gotoXY (x, y);
  bc_printA ((char)ACS_ULCORNER);
  mt_gotoXY (x + width - 1, y);
  bc_printA ((char)ACS_URCORNER);
  mt_gotoXY (x + width - 1, y + height - 1);
  bc_printA ((char)ACS_LRCORNER);
  mt_gotoXY (x, y + height - 1);
  bc_printA ((char)ACS_LLCORNER);

  /* Горизонтальные линии */
  for (int i = 1; i < width - 1; ++i)
    {
      // верхняя
      mt_gotoXY (x + i, y);
      bc_printA ((char)ACS_HLINE);
      // нижняя
      mt_gotoXY (x + i, y + height - 1);
      bc_printA ((char)ACS_HLINE);
    }

  /* Вертикальные линии */
  for (int i = 1; i < height - 1; ++i)
    {
      // верхняя
      mt_gotoXY (x, y + i);
      bc_printA ((char)ACS_VLINE);
      // нижняя
      mt_gotoXY (x + width - 1, y + i);
      bc_printA ((char)ACS_VLINE);
    }
  return 0;
}

int
bc_printBigChar (unsigned int *big, int x, int y, enum colors colorFG,
                 enum colors colorBG)
{
  if (colorFG != DEFAULT)
    mt_setfgcolor (colorFG);
  if (colorBG != DEFAULT)
    mt_setbgcolor (colorBG);

  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      {
        mt_gotoXY (x + i, y + j);
        int value;
        if (bc_getbigCharPos (big, i, j, &value))
          return -1;
        if (value)
          bc_printA (ACS_CKBOARD);
        if (!value)
          {
            snprintf (buf, 6, "%c ", ' ');
          }
        write (1, buf, strlen (buf));
      }

  set_default_color ();
  return 0;
}

int
bc_setBigCharPos (int *big, int x, int y, int value)
{
  if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return -1;
  if (value)
    big[(int)(y / 4)] |= (1 << (8 * (y % 4) + (7 - x)));
  else
    big[(int)(y / 4)] &= ~(1 << (8 * (y % 4) + (7 - x)));
  return 0;
}

int
bc_getbigCharPos (int *big, int x, int y, int *value)
{
  if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return -1;
  if ((big[(int)(y / 4)] & (1 << (8 * (y % 4) + (7 - x)))) != 0)
    *value = 1;
  else
    *value = 0;
  return 0;
}

int
bc_bigCharWrite (int fd, int *big, int count)
{
  if (write (fd, big, count * 2 * sizeof (unsigned int)))
    return -1;
  return 0;
}

int
bc_bigCharRead (int fd, int *big, int need_count, int *count)
{
  *count = 0;
  for (int i = 0; i < need_count * 2; ++i)
    {
      if (read (fd, &big[i], sizeof (unsigned int)) == -1)
        return -1;
      if (!((i + 1) % 2))
        (*count)++;
    }

  return 0;
}