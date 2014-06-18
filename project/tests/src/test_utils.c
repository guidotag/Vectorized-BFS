#include "../include/test_utils.h"

void test_utils_to_base(){
	printf("\ntest_utils_to_base\n");
	char *str;
	
	assert(strcmp(str = to_base(17, 2, 0), "10001") == 0);
	free(str);
	assert(strcmp(str = to_base(17, 2, 1), "10001") == 0);
	free(str);
	assert(strcmp(str = to_base(17, 2, 7), "0010001") == 0);
	free(str);
	assert(strcmp(str = to_base(24, 2, 0), "11000") == 0);
	free(str);
	assert(strcmp(str = to_base(24, 2, 10), "0000011000") == 0);
	free(str);
	assert(strcmp(str = to_base(0, 2, 0), "0") == 0);
	free(str);
	assert(strcmp(str = to_base(0, 2, 8), "00000000") == 0);
	free(str);
	assert(strcmp(str = to_base(16, 2, 0), "10000") == 0);
	free(str);
	assert(strcmp(str = to_base(17, 16, 0), "11") == 0);
	free(str);
	assert(strcmp(str = to_base(455375, 16, 0), "6f2cf") == 0);
	free(str);
	assert(strcmp(str = to_base(455375, 16, 10), "000006f2cf") == 0);
	free(str);
}

void test_utils_length_base(){
	printf("\ntest_utils_length_base\n");
	assert(length_base(17, 2) == 5);
	assert(length_base(24, 2) == 5);
	assert(length_base(0, 2) == 1);
	assert(length_base(16, 2) == 5);
	assert(length_base(17, 16) == 2);
	assert(length_base(455375, 16) == 5);
}

void test_utils_log(){
	printf("\ntest_utils_log\n");
	assert(_log(16, 2) == 4);
	assert(_log(1, 2) == 0);
	assert(_log(4, 2) == 2);
	assert(_log(5, 2) == 2);
	assert(_log(9, 2) == 3);
	assert(_log(19, 16) == 1);
	assert(_log(16, 16) == 1);
	assert(_log(83, 5) == 2);
}

void test_utils_ceil(){
	printf("\ntest_utils_ceil\n");
	assert(_ceil(4.01) == 5);
	assert(_ceil(0.0014) == 1);
	assert(_ceil(0.99) == 1);
	assert(_ceil(16.28) == 17);
}

void test_utils_random(){
	printf("\ntest_utils_random\n");
	srand(time(NULL));
	printf("random(%i, %i) = %i\n", -3, 8, random(-3, 8));
	printf("random(%i, %i) = %i\n", 1, 2, random(1, 2));
	printf("random(%i, %i) = %i\n", 0, 0, random(0, 0));
	printf("random(%i, %i) = %i\n", 1, 10, random(1, 10));
}

void test_utils(){	
	test_utils_to_base();
	test_utils_length_base();
	test_utils_log();
	test_utils_ceil();
	test_utils_random();
}
