#ifndef SIMPLECOMPUTER_H
#define SIMPLECOMPUTER_H

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h> // for write function
#define N 100

#define REGISTER_SIZE 5

#define OVERFLOW 0               // переполнение
#define DIVISION_ERROR_BY_ZERO 1 // ошибка деления на 0
#define OUT_OF_MEMORY 2          // выход за границы памяти
#define IGNORING_CLOCK_PULSES 3 // игнорирование тактовых импульсов
#define INVALID_COMMAND 4 // неверная команда

extern short int memory_arr[N];
extern char flag;
extern short currMemCell;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit ();
int sc_regSet (int _register, int value);
int sc_regGet (int _register, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);

#endif