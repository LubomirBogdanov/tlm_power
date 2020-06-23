#include <stdio.h>
#include "straight_func.h"

int ddiv(int a, int b ){
    //return (int)(a/b);
    return ( (int) (((a)<0) ? ((a)-(b)+1)/(b) : (a)/(b)) ); 
    //return ( (int) (((a)<0)^((b)<0) ? ((a) < 0 ? ((a)-(b)+1)/(b) : ((a)-(b)-1)/(b)) : (a)/(b)) ); 
}

int mod(int a, int b){
    return mod(a, b);
}

int ceil1(int a){
    return a; /* return (int) ceil(a);*/
}

int floor1(int a){
    return a; /* return (int) floor(a);*/
}

void  _in_numbers_stream( tCH_1 *out_0ND_0 ) {
    in_numbers_stream( out_0ND_0 );
}

void  _out_numbers_stream( tCH_1 in_0ND_1 ) {
    out_numbers_stream( in_0ND_1 );
}

const int numbers_array[5] = { 13, 3, 24, 17, 54};

void in_numbers_stream(int *out){
	static int index = 0;

	*out = numbers_array[index++];
}

volatile int numbers_array_sorted[12];

void out_numbers_stream(const int in_1){
	static int index = 0;
	numbers_array_sorted[index++] = in_1;
}

/*!
	\brief 

	return 1 - arrays don't match, 0 - arrays match
*/
uint8_t numbers_check(void){
	uint8_t i;
	for(i = 0; i < 5; i++){
		if(numbers_array[i] != numbers_array_sorted[i]){
			return 1;
		}
	}

	return 0;
}
