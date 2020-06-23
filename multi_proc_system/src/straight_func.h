#ifndef _FUNC_H
#define _FUNC_H

#include <stdint.h>

typedef int tCH_1;

int ddiv(int a, int b );
int mod(int a, int b);
int ceil1(int a);
int floor1(int a);

void  _in_numbers_stream(tCH_1 *out_0ND_0);
void  _out_numbers_stream(tCH_1 in_0ND_1);
void in_numbers_stream(int *out);
void out_numbers_stream(const int in_1);
uint8_t numbers_check(void);

#endif 
