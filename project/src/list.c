#include "../include/list.h"

list *new_l(){
	list *l = (list *) malloc(sizeof(list));
	l->first = NULL;
	l->last = NULL;
	return l;
}

int back_l(list *l){
	assert(l->first != NULL);
	
	int e = l->last->e;
	node_l *prev = l->last->prev;
	
	free(l->last);
	
	if(prev == NULL){
		l->first = NULL;
		l->last = NULL;
	}else{
		prev->next = NULL;
		l->last = prev;
	}
	
	return e;
}

void append_front_l(list *l, int e){
	node_l *n = (node_l *) malloc(sizeof(node_l));
	n->e = e;
	n->next = l->first;
	n->prev = NULL;
	
	if(l->first != NULL){
		l->first->prev = n;
	}
	
	l->first = n;
	
	if(l->last == NULL){
		l->last = n;
	}
}

void print_l(list *l){
	assert(l != NULL);
		
	if(l->first == NULL){
		printf("Empty list\n");
	}else{
		node_l *n = l->first;
		
		while(n != NULL){
			printf("%i", n->e);
			n = n->next;
			
			if(n != NULL){
				printf(" <-> ");
			}
		}
	}
	
	printf("\n");
}

void destroy_l(list *l){
	assert(l != NULL);
	
	node_l *n = l->first;
	
	while(n != NULL){
		node_l *next = n->next;
		free(n);
		n = next;
	}
	
	free(l);
}
