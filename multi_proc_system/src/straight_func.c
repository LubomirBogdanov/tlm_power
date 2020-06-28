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
#include <stdio.h>
#include "straight_func.h"

volatile uint8_t numbers_array_sorted[NUM_OF_TOKENS];

#if NUM_OF_TOKENS == 5
	const int numbers_array[NUM_OF_TOKENS] = { 13, 3, 24, 17, 54};
#endif

#if NUM_OF_TOKENS == 50
	const int numbers_array[NUM_OF_TOKENS] = {
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96
	};
#endif

#if NUM_OF_TOKENS == 500
	const uint8_t numbers_array[NUM_OF_TOKENS] = {
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
			13, 3, 24, 17, 54, 22, 64, 31, 89, 77,
			5, 234, 2, 44, 16, 95, 102, 76, 204, 31,
			8, 3, 90, 91, 18, 135, 46, 4, 0, 255,
			210, 233, 169, 70, 60, 33, 52, 87, 55, 69,
			189, 11, 199, 211, 249, 127, 128, 65, 41, 96,
	};
#endif

int ddiv(int a, int b ){
    //return (int)(a/b);
    return ( (int) (((a)<0) ? ((a)-(b)+1)/(b) : (a)/(b)) ); 
    //return ( (int) (((a)<0)^((b)<0) ? ((a) < 0 ? ((a)-(b)+1)/(b) : ((a)-(b)-1)/(b)) : (a)/(b)) ); 
}

int mod(int a, int b){
    return mod(a, b);
}

int ceil1(int a){
    return a; // return (int) ceil(a);
}

int floor1(int a){
    return a; // return (int) floor(a);
}

void  _in_numbers_stream( tCH_1 *out_0ND_0 ) {
    in_numbers_stream( out_0ND_0 );
}

void  _out_numbers_stream( tCH_1 in_0ND_1 ) {
    out_numbers_stream( in_0ND_1 );
}

void in_numbers_stream(int *out){
	static int index = 0;

	*out = numbers_array[index++];
}

void out_numbers_stream(const int in_1){
	static int index = 0;
	numbers_array_sorted[index++] = in_1;
}

/*!
	\brief numbers_check - a function for verifying 
	data token transfers.

	return 1 - arrays don't match, 0 - arrays match
*/
uint8_t numbers_check(void){
	uint8_t i;
	for(i = 0; i < NUM_OF_TOKENS; i++){
		if(numbers_array[i] != numbers_array_sorted[i]){
			return 1;
		}
	}

	return 0;
}
