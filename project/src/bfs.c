#include "../include/list.h"
#include "../include/queue.h"

void bfs(list **adj_lists, int *sources, int n){
	queue *q = new_q();
	int i;
	
	for(i = 0; i < n; i++){
		if(sources[i] == 1){
			push_q(q, i);
		}
	}
	
	while(!is_empty_q(q)){
		int v = pop_q(q);
		node_l *n = adj_lists[v]->first;
		while(n != NULL){
			int u = n->e;
			if(sources[u] == 0){
				sources[u] = 1;
				push_q(q, u);
			}
			
			n = n->next;
		}
	}
	
	destroy_q(q);
}
