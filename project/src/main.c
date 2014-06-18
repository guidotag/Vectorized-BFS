#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <assert.h>
#include "../include/defines.h"
#include "../include/bmatrix.h"
#include "../include/list.h"
#include "../include/timing.h"
#include "../include/utils.h"

#define OUTPUT_FILE_NAME_MAX_LEN 100

const char* program_name;

extern void vectorized_bfs_no_branching(bmatrix *adj_matrix, bmatrix *sources);
extern void vectorized_bfs_branching(bmatrix *adj_matrix, bmatrix *sources);
extern void bfs(list **adj_lists, int *sources, int n);

void doit(int n, double pr_adj, double pr_src){	
	srand(time(NULL));
	
	/* Set the adjacency matrix, lists and sources set */
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
	
	/* Run each implementation */
	unsigned long long start, end;
	START_CLOCK(start);
	bfs(adj_lists, sources, n);
	STOP_CLOCK(end);
	
	printf("%llu ", end - start);
	
	START_CLOCK(start);
	vectorized_bfs_branching(adj_matrix, bm_sources);
	STOP_CLOCK(end);
	
	printf("%llu ", end - start);
	
	START_CLOCK(start);
	vectorized_bfs_no_branching(adj_matrix, bm_sources_copy);
	STOP_CLOCK(end);
	
	printf("%llu", end - start);

	destroy_bm(adj_matrix);
	destroy_bm(bm_sources);
	destroy_bm(bm_sources_copy);
	
	for(i = 0; i < n; i++){
		destroy_l(adj_lists[i]);
	}
	
	free(adj_lists);
	free(sources);	
}

void print_help(){
	printf("Usage of the program:\n");
	printf("\t%s <options> [parameters]\n", program_name);
	printf("The available options are:\n");
	printf("\t> -h, -help\n\tPrints help information\n");
	printf("\t> -f, -file <file_name>\n\tOutput to a specific file\n");
	printf("There are three parameters:\n");
	printf("\t> n\n\tThe number of nodes of the graph\n");
	printf("\t> pr_adj\n\tThe graph density parameter\n");
	printf("\t> pr_src\n\tThe sources density parameter\n");
	printf("Output's format:\n");
	printf("\tn pr_adj pr_src t1 t2 t3\n");
	printf("where\n");
	printf("\tt1 = bfs tsc\n");
	printf("\tt2 = vectorized_bfs_branching tsc\n");
	printf("\tt3 = vectorized_bfs_no_branching tsc\n");
	printf("Example call:\n");
	printf("\t%s -f output.out 100 0.75 0.1\n", program_name);
}

int main(int argc, char *argv[]){
	int n;
	double pr_adj;
	double pr_src;
	bool redirect_output = FALSE;
	char output_file[10 + OUTPUT_FILE_NAME_MAX_LEN];
	
	program_name = argv[0];
	
	/* Options */
	const char* const optstring = "hf:";

	const struct option longops[] = {
		{"help", 0, NULL, 'h'},
		{"file", 1, NULL, 'f'},
		{NULL, 0, NULL, 0}
	};
	
	if(argc < 4){
		print_help();
		exit(EXIT_SUCCESS);
	}
	
	while(1){
		int next_opt = getopt_long(argc, argv, optstring, longops, NULL);
		
		if(next_opt == -1){
			break;
		}
		
		switch(next_opt){
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
			case 'f':
				if(strlen(optarg) > OUTPUT_FILE_NAME_MAX_LEN){
					abort();
				}
				redirect_output = TRUE;
				strcat(output_file, "./output/");
				strcat(output_file, optarg);
				break;
			default:
				abort();
		}
	}
	
	n = atoi(argv[argc - 3]);
	pr_adj = atof(argv[argc - 2]);
	pr_src = atof(argv[argc - 1]);
	
	if(redirect_output){
		fopen(output_file, "a");
		freopen(output_file, "a", stdout);
	}
	
	printf("%i %f %f ", n, pr_adj, pr_src);
	
	doit(n, pr_adj, pr_src);
	
	printf("\n");
	
	return 0;
}
