#include "../include/test_bfs.h"

/*
 * 0 --> 1 <-- 2 <-- 3 <-- 4
 *       |	   |     ʌ     |
 *       v     v     |     v
 * 5 <-- 6 --> 7 --> 8 --> 9
 * 
 * Sources = {0}
 * 
 * Reachable nodes: 0, 1, 2, 3, 5, 6, 7, 8, 9
 */
void test_bfs_serial_bfs_1(){
	printf("\ntest_bfs_serial_bfs_1\n");
	
	int n = 10;
	list **adj_lists = (list **) malloc(sizeof(list *) * n);
	int *sources = (int *) malloc(sizeof(int) * n);
	
	sources[0] = 1;
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 0){
			sources[i] = 0;
		}
	}
	
	for(i = 0; i < n; i++){
		adj_lists[i] = new_l();
	}

	append_front_l(adj_lists[0], 1);

	append_front_l(adj_lists[1], 6);

	append_front_l(adj_lists[2], 1);
	append_front_l(adj_lists[2], 7);

	append_front_l(adj_lists[3], 2);

	append_front_l(adj_lists[4], 3);
	append_front_l(adj_lists[4], 9);
	
	append_front_l(adj_lists[6], 5);
	append_front_l(adj_lists[6], 7);
	
	append_front_l(adj_lists[7], 8);

	append_front_l(adj_lists[8], 3);
	append_front_l(adj_lists[8], 9);
	
	bfs(adj_lists, sources, n);
	
	assert(sources[4] == 0);
	
	for(i = 0; i < n; i++){
		if(i != 4){
			assert(sources[i] == 1);
		}
	}
	
	for(i = 0; i < n; i++){
		destroy_l(adj_lists[i]);
	}
	
	free(adj_lists);
	free(sources);
}

/*
 *        4 --> 5 --> 6   14
 *        ʌ           |   ʌ
 *        |           v   |        
 *  0 --> 1 <-- 2 <-- 7   8 --> 9 <-- 10
 *        ʌ    
 *        |  
 *        3               11 --> 12 --> 13
 * 
 * Sources = {3, 7, 8}
 * 
 * Reachable nodes: 1, 2, 3, 4, 5, 6, 7, 8, 9, 14
 */
void test_bfs_serial_bfs_2(){
	printf("\ntest_bfs_serial_bfs_2\n");
	
	int n = 15;
	list **adj_lists = (list **) malloc(sizeof(list *) * n);
	int *sources = (int *) malloc(sizeof(int) * n);
	
	sources[3] = 1;
	sources[7] = 1;
	sources[8] = 1;
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 3 && i != 7 && i != 8){
			sources[i] = 0;
		}
	}
	
	for(i = 0; i < n; i++){
		adj_lists[i] = new_l();
	}

	append_front_l(adj_lists[0], 1);
	
	append_front_l(adj_lists[1], 4);
	
	append_front_l(adj_lists[2], 1);
	
	append_front_l(adj_lists[3], 1);
	
	append_front_l(adj_lists[4], 5);
	
	append_front_l(adj_lists[5], 6);
	
	append_front_l(adj_lists[6], 7);
	
	append_front_l(adj_lists[7], 2);
	
	append_front_l(adj_lists[8], 14);
	append_front_l(adj_lists[8], 9);
	
	append_front_l(adj_lists[10], 9);
	
	append_front_l(adj_lists[11], 12);
	
	append_front_l(adj_lists[12], 13);
	
	bfs(adj_lists, sources, n);
	
	assert(sources[0] == 0);
	assert(sources[10] == 0);
	assert(sources[11] == 0);
	assert(sources[12] == 0);
	assert(sources[13] == 0);
	
	for(i = 0; i < n; i++){
		if(i != 0 && i != 10 && i != 11 && i != 12 && i != 13){
			assert(sources[i] == 1);
		}
	}
	
	for(i = 0; i < n; i++){
		destroy_l(adj_lists[i]);
	}
	
	free(adj_lists);
	free(sources);
}

/*
 * 0 --> 1 <-- 2 <-- 3 <-- 4
 *       |	   |     ʌ     |
 *       v     v     |     v
 * 5 <-- 6 --> 7 --> 8 --> 9
 * 
 * Sources = {0}
 * 
 * Reachable nodes: 0, 1, 2, 3, 5, 6, 7, 8, 9
 */
void test_bfs_vectorized_bfs_branching_1(){
	printf("\ntest_bfs_vectorized_bfs_no_branching_1\n");
	
	int n = 10;
	
	bmatrix *adj_matrix = new_bm(n, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	
	set_bit_bm(bm_sources, 0, 0);
	
	set_bit_bm(adj_matrix, 0, 1);
	set_bit_bm(adj_matrix, 1, 6);
	set_bit_bm(adj_matrix, 2, 1);
	set_bit_bm(adj_matrix, 2, 7);
	set_bit_bm(adj_matrix, 3, 2);
	set_bit_bm(adj_matrix, 4, 3);
	set_bit_bm(adj_matrix, 4, 9);
	set_bit_bm(adj_matrix, 6, 5);
	set_bit_bm(adj_matrix, 6, 7);
	set_bit_bm(adj_matrix, 7, 8);
	set_bit_bm(adj_matrix, 8, 3);
	set_bit_bm(adj_matrix, 8, 9);
	
	vectorized_bfs_branching(adj_matrix, bm_sources);
	
	assert(get_bit_bm(bm_sources, 0, 4) == 0);
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 4){
			assert(get_bit_bm(bm_sources, 0, i) == 1);
		}
	}
	
	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
}

/*
 *        4 --> 5 --> 6   14
 *        ʌ           |   ʌ
 *        |           v   |        
 *  0 --> 1 <-- 2 <-- 7   8 --> 9 <-- 10
 *        ʌ    
 *        |  
 *        3               11 --> 12 --> 13
 * 
 * Sources = {3, 7, 8}
 * 
 * Reachable nodes: 1, 2, 3, 4, 5, 6, 7, 8, 9, 14
 */
void test_bfs_vectorized_bfs_branching_2(){
	printf("\ntest_bfs_vectorized_bfs_branching_2\n");
	
	int n = 15;
	
	bmatrix *adj_matrix = new_bm(n, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	
	set_bit_bm(bm_sources, 0, 3);
	set_bit_bm(bm_sources, 0, 7);
	set_bit_bm(bm_sources, 0, 8);
	
	set_bit_bm(adj_matrix, 0, 1);
	set_bit_bm(adj_matrix, 1, 4);
	set_bit_bm(adj_matrix, 2, 1);
	set_bit_bm(adj_matrix, 3, 1);
	set_bit_bm(adj_matrix, 4, 5);
	set_bit_bm(adj_matrix, 5, 6);
	set_bit_bm(adj_matrix, 6, 7);
	set_bit_bm(adj_matrix, 7, 2);
	set_bit_bm(adj_matrix, 8, 14);
	set_bit_bm(adj_matrix, 8, 9);
	set_bit_bm(adj_matrix, 10, 9);
	set_bit_bm(adj_matrix, 11, 12);
	set_bit_bm(adj_matrix, 12, 13);
	
	vectorized_bfs_branching(adj_matrix, bm_sources);
	
	assert(get_bit_bm(bm_sources, 0, 0) == 0);
	assert(get_bit_bm(bm_sources, 0, 10) == 0);
	assert(get_bit_bm(bm_sources, 0, 11) == 0);
	assert(get_bit_bm(bm_sources, 0, 12) == 0);
	assert(get_bit_bm(bm_sources, 0, 13) == 0);
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 0 && i != 10 && i != 11 && i != 12 && i != 13){
			assert(get_bit_bm(bm_sources, 0, i) == 1);
		}
	}
	
	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
}

/*
 * 0 --> 1 <-- 2 <-- 3 <-- 4
 *       |	   |     ʌ     |
 *       v     v     |     v
 * 5 <-- 6 --> 7 --> 8 --> 9
 * 
 * Sources = {0}
 * 
 * Reachable nodes: 0, 1, 2, 3, 5, 6, 7, 8, 9
 */
void test_bfs_vectorized_bfs_no_branching_1(){
	printf("\ntest_bfs_vectorized_bfs_no_branching_1\n");
	
	int n = 10;
	
	bmatrix *adj_matrix = new_bm(n, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	
	set_bit_bm(bm_sources, 0, 0);
	
	set_bit_bm(adj_matrix, 0, 1);
	set_bit_bm(adj_matrix, 1, 6);
	set_bit_bm(adj_matrix, 2, 1);
	set_bit_bm(adj_matrix, 2, 7);
	set_bit_bm(adj_matrix, 3, 2);
	set_bit_bm(adj_matrix, 4, 3);
	set_bit_bm(adj_matrix, 4, 9);
	set_bit_bm(adj_matrix, 6, 5);
	set_bit_bm(adj_matrix, 6, 7);
	set_bit_bm(adj_matrix, 7, 8);
	set_bit_bm(adj_matrix, 8, 3);
	set_bit_bm(adj_matrix, 8, 9);
	
	vectorized_bfs_no_branching(adj_matrix, bm_sources);
	
	assert(get_bit_bm(bm_sources, 0, 4) == 0);
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 4){
			assert(get_bit_bm(bm_sources, 0, i) == 1);
		}
	}
	
	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
}

/*
 *        4 --> 5 --> 6   14
 *        ʌ           |   ʌ
 *        |           v   |        
 *  0 --> 1 <-- 2 <-- 7   8 --> 9 <-- 10
 *        ʌ    
 *        |  
 *        3               11 --> 12 --> 13
 * 
 * Sources = {3, 7, 8}
 * 
 * Reachable nodes: 1, 2, 3, 4, 5, 6, 7, 8, 9, 14
 */
void test_bfs_vectorized_bfs_no_branching_2(){
	printf("\ntest_bfs_vectorized_bfs_no_branching_2\n");
	
	int n = 15;
	
	bmatrix *adj_matrix = new_bm(n, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	
	set_bit_bm(bm_sources, 0, 3);
	set_bit_bm(bm_sources, 0, 7);
	set_bit_bm(bm_sources, 0, 8);
	
	set_bit_bm(adj_matrix, 0, 1);
	set_bit_bm(adj_matrix, 1, 4);
	set_bit_bm(adj_matrix, 2, 1);
	set_bit_bm(adj_matrix, 3, 1);
	set_bit_bm(adj_matrix, 4, 5);
	set_bit_bm(adj_matrix, 5, 6);
	set_bit_bm(adj_matrix, 6, 7);
	set_bit_bm(adj_matrix, 7, 2);
	set_bit_bm(adj_matrix, 8, 14);
	set_bit_bm(adj_matrix, 8, 9);
	set_bit_bm(adj_matrix, 10, 9);
	set_bit_bm(adj_matrix, 11, 12);
	set_bit_bm(adj_matrix, 12, 13);
	
	vectorized_bfs_no_branching(adj_matrix, bm_sources);
	
	assert(get_bit_bm(bm_sources, 0, 0) == 0);
	assert(get_bit_bm(bm_sources, 0, 10) == 0);
	assert(get_bit_bm(bm_sources, 0, 11) == 0);
	assert(get_bit_bm(bm_sources, 0, 12) == 0);
	assert(get_bit_bm(bm_sources, 0, 13) == 0);
	
	int i;
	for(i = 0; i < n; i++){
		if(i != 0 && i != 10 && i != 11 && i != 12 && i != 13){
			assert(get_bit_bm(bm_sources, 0, i) == 1);
		}
	}
	
	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
}

void test_bfs_mixed(){
	printf("\ntest_bfs_mixed\n");
	
	srand(time(NULL));
	
	double pr_adj = 0.005;
	double pr_src = 0.01;
	int n = 256;
	
	bmatrix *adj_matrix = new_bm(n, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);
	bmatrix *bm_sources_copy = new_bm(1, _ceil(n / (8.0 * BYTES_PER_BMATRIX_ROW_FACTOR)) * BYTES_PER_BMATRIX_ROW_FACTOR);

	list **adj_lists = (list **) malloc(sizeof(list *) * n);
	int *sources = (int *) malloc(sizeof(int) * n);
	
	int i, j;
	for(i = 0; i < n; i++){
		double u;
		u = rand() / (double) RAND_MAX;
		if(u < pr_src){
			sources[i] = 1;
			set_bit_bm(bm_sources, 0, i);
			set_bit_bm(bm_sources_copy, 0, i);
		}else{
			sources[i] = 0;
		}
		
		adj_lists[i] = new_l();
		for(j = 0; j < n; j++){
			u = rand() / (double) RAND_MAX;
			if(u < pr_adj){
				set_bit_bm(adj_matrix, i, j);
				append_front_l(adj_lists[i], j);
			}
		}
	}

	bfs(adj_lists, sources, n);
	vectorized_bfs_branching(adj_matrix, bm_sources);
	vectorized_bfs_no_branching(adj_matrix, bm_sources_copy);
	
	for(i = 0; i < n; i++){
		assert(sources[i] == get_bit_bm(bm_sources, 0, i));
		assert(sources[i] == get_bit_bm(bm_sources_copy, 0, i));
	}
	
	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
	destroy_bm(bm_sources_copy);
	
	for(i = 0; i < n; i++){
		destroy_l(adj_lists[i]);
	}
	
	free(adj_lists);
	free(sources);
}

void test_bfs(){
	test_bfs_serial_bfs_1();
	test_bfs_serial_bfs_2();
	test_bfs_vectorized_bfs_branching_1();
	test_bfs_vectorized_bfs_branching_2();
	test_bfs_vectorized_bfs_no_branching_1();
	test_bfs_vectorized_bfs_no_branching_2();
	test_bfs_mixed();
}
