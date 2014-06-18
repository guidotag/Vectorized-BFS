#include "../include/queue.h"

queue *new_q(){
	queue *q = (queue *) malloc(sizeof(queue));
	q->l = new_l();
	
	return q;
}

void push_q(queue *q, int e){
	append_front_l(q->l, e);
}

int pop_q(queue *q){
	int e = back_l(q->l);
	return e;
}

bool is_empty_q(queue *q){
	return q->l->first == NULL;
}

void destroy_q(queue *q){
	destroy_l(q->l);
	free(q);
}
