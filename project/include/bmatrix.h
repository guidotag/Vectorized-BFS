/*
 * Bit matrix data structure. Specifically a matrix represented as an array of bits.
 * Each bit is a real memory bit.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdint.h>
#include "utils.h"
#include "defines.h"

typedef struct bmatrix{
	void *initial;
	
	uint rows;

	uint bytes_per_row;
} bmatrix ;

/*
 * Creates and returns a new bit matrix. Each bit is set to 0.
 */
bmatrix *new_bm(uint rows, uint bytes_per_row);

/*
 * Sets to 1 the bit in row i and column j.
 */
void set_bit_bm(bmatrix *bm, uint i, uint j);

/*
 * Returns the value of the bit in row i and column j.
 */
uint get_bit_bm(bmatrix *bm, uint i, uint j);

/*
 * Prints the matrix.
 */
void print_bm(bmatrix *bm);

/*
 * Destroys the matrix.
 */
void destroy_bm(bmatrix *bm);

#endif
