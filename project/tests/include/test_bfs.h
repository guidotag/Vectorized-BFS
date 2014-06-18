/*
 * bfs.c and vectorized_bfs.asm functions tests.
 */

#ifndef __TEST_BFS_H__
#define __TEST_BFS_H__

#include <stdlib.h>
#include <time.h>
#include "../../include/list.h"
#include "../../include/bmatrix.h"

extern void vectorized_bfs_no_branching(bmatrix *adj_matrix, bmatrix *sources);
extern void vectorized_bfs_branching(bmatrix *adj_matrix, bmatrix *sources);
extern void bfs(list **adj_lists, int *sources, int n);

void test_bfs_serial_bfs_1();
void test_bfs_serial_bfs_2();
void test_bfs_vectorized_bfs_branching_1();
void test_bfs_vectorized_bfs_branching_2();
void test_bfs_vectorized_bfs_no_branching_1();
void test_bfs_vectorized_bfs_no_branching_2();
void test_bfs_mixed();

void test_bfs();

#endif
