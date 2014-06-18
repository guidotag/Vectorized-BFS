/*
 * Defines and typedefs.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef enum bool{
	TRUE = 1, FALSE = 0
} bool;

typedef unsigned char uchar;
typedef unsigned int uint;

#define BYTES_PER_BMATRIX_ROW_FACTOR 16		/* Each bit matrix's row size (in bytes) will be a multiple of this number */

#endif
