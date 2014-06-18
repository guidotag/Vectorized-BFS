#include "../include/test_bmatrix.h"

void test_bmatrix_set_bits(){
	printf("\ntest_bmatrix_set_bits\n");
	bmatrix *bm = new_bm(37, 5);
	
	/* The bmatrix is full of zeroes. */
	
	print_bm(bm);
	
	set_bit_bm(bm, 0, 0);
	set_bit_bm(bm, 0, 1);
	set_bit_bm(bm, 1, 2);
	set_bit_bm(bm, 1, 10);
	set_bit_bm(bm, 1, 11);
	set_bit_bm(bm, 5, 17);
	set_bit_bm(bm, 10, 0);
	set_bit_bm(bm, 21, 12);
	set_bit_bm(bm, 1, 35);
	set_bit_bm(bm, 36, 5);
	set_bit_bm(bm, 36, 36);
	
	print_bm(bm);
	
	destroy_bm(bm);
}

void test_bmatrix_get_bits(){
	printf("\ntest_bmatrix_get_bits\n");
	bmatrix *bm = new_bm(37, 5);

	/* We fill the matrix the same way as in test_bmatrix_set_bits. */
	
	set_bit_bm(bm, 0, 0);
	set_bit_bm(bm, 0, 1);
	set_bit_bm(bm, 1, 2);
	set_bit_bm(bm, 1, 10);
	set_bit_bm(bm, 1, 11);
	set_bit_bm(bm, 5, 17);
	set_bit_bm(bm, 10, 0);
	set_bit_bm(bm, 21, 12);
	set_bit_bm(bm, 1, 35);
	set_bit_bm(bm, 36, 5);
	set_bit_bm(bm, 36, 36);
	
	assert(get_bit_bm(bm, 0, 0) == 1);
	assert(get_bit_bm(bm, 0, 2) == 0);
	assert(get_bit_bm(bm, 1, 10) == 1);
	assert(get_bit_bm(bm, 1, 15) == 0);
	assert(get_bit_bm(bm, 36, 4) == 0);
	assert(get_bit_bm(bm, 36, 5) == 1);
	assert(get_bit_bm(bm, 36, 36) == 1);
		
	destroy_bm(bm);
}

void test_bmatrix(){
	test_bmatrix_set_bits();
	test_bmatrix_get_bits();
}
