
#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include "myTerm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* Псевдографика */
#define ACS_CKBOARD 'a'  // Штриховка
#define ACS_ULCORNER 'l' // Левый верхний угол
#define ACS_URCORNER 'k' // Правый верхний угол
#define ACS_LRCORNER 'j' // Правый нижний угол
#define ACS_LLCORNER 'm' // Левый нижний угол
#define ACS_HLINE 'q'    // Горизонтальная линия
#define ACS_VLINE 'x'    // Вертикальная линия

extern unsigned int big_chars[][2];

int bc_printA (char charr);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printBigChar (unsigned int *big, int x, int y, enum colors colorFG,
                     enum colors colorBG);
int bc_setBigCharPos (int *big, int x, int y, int value);
int bc_getbigCharPos (int *big, int x, int y, int *value);
int bc_bigCharWrite (int fd, int *big, int count);
int bc_bigCharRead (int fd, int *big, int need_count, int *count);

#endif