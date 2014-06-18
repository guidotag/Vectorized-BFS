#include "../include/bmatrix.h"

bmatrix *new_bm(uint rows, uint bytes_per_row){	
	bmatrix *bm = (bmatrix *) malloc(sizeof(bmatrix));
	
	bm->bytes_per_row = bytes_per_row;
	bm->rows = rows;
	bm->initial = malloc(bytes_per_row * rows);

	uchar *ptr = (uchar *) bm->initial;
	int count = 0;
	
	while(count < rows * bytes_per_row){
		count++;
		*ptr = 0;
		ptr++;
	}
	
	return bm;
}

void set_bit_bm(bmatrix *bm, uint i, uint j){
	assert(bm != NULL);
	assert(i >= 0 && i < bm->rows);
	assert(j >= 0 && j < 8 * bm->bytes_per_row);

	uchar *ptr = (uchar *)((uintptr_t) bm->initial + bm->bytes_per_row * i + (int) (j / 8));
	
	*ptr = *ptr | (1 << (7 - (j % 8)));
}

uint get_bit_bm(bmatrix *bm, uint i, uint j){
	assert(bm != NULL);
	assert(i >= 0 && i < bm->rows);
	assert(j >= 0 && j < 8 * bm->bytes_per_row);
	
	uchar *ptr = (uchar *)((uintptr_t) bm->initial + bm->bytes_per_row * i + (int) (j / 8));
	
	int offset = 7 - (j % 8);
	
	return (*ptr & (1 << offset)) >> offset;
}

void print_bm(bmatrix *bm){
	assert(bm != NULL);
	uchar *ptr = (uchar *) bm->initial;
	int count = 0;
	
	while(count < bm->rows * bm->bytes_per_row){	
		char *str;
		printf("%s ", str = to_base((unsigned long long) *ptr, 2, 8));	
		free(str);
		ptr++;
		count++;
		
		if(count % bm->bytes_per_row == 0){
			printf("\n");
		}
	}
}

void destroy_bm(bmatrix *bm){
	assert(bm != NULL);
	free(bm->initial);
	free(bm);
}
