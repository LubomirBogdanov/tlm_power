#include <stdio.h>
#include "sort_func.h"

void in_numbers_stream(int *out){
	static int index = 0;
	const int numbers_array[12] = { 13, 3, 24, 17, 54, 2, 19, 63, 46, 9, 75, 38};

	*out = numbers_array[index++];
 }

void compare_numbers(const int *in_1, const int *in_2, int *out_1, int *out_2){
	 int tmp1 = *in_1 > *in_2 ? *in_2 : *in_1;
	 int tmp2 = *in_1 > *in_2 ? *in_1 : *in_2;
	 *out_1 = tmp1;
	 *out_2 = tmp2;
}

void out_numbers_stream(const int *in_1){
	static int index = 0;
	int numbers_array_sorted[12];

	numbers_array_sorted[index++] = *in_1;
}
