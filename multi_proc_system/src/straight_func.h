/*
    Copyright (C) 2020 Lubomir Bogdanov
    Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>
    This file is part of tlm_power project.
    tlm_power is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    tlm_power is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with tlm_power.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _FUNC_H
#define _FUNC_H

#include <stdint.h>

//#define NUM_OF_TOKENS	5
//#define NUM_OF_TOKENS	50
#define NUM_OF_TOKENS	500

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
