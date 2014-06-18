#include "../include/test_queue.h"

void test_queue_push(){
	printf("\ntest_queue_push\n");
	
	queue *q = new_q();
	
	push_q(q, 10);
	push_q(q, 0);
	push_q(q, -162);
	push_q(q, 13);
	push_q(q, 20);
	
	destroy_q(q);
}

void test_queue_pop(){
	printf("\ntest_queue_pop\n");
	
	queue *q = new_q();
	
	push_q(q, 10);
	push_q(q, 0);
	push_q(q, -162);
	push_q(q, 13);
	push_q(q, 20);
	
	assert(pop_q(q) == 10);
	assert(pop_q(q) == 0);
	
	push_q(q, 10);
	
	assert(pop_q(q) == -162);
	assert(pop_q(q) == 13);
	assert(pop_q(q) == 20);
	assert(pop_q(q) == 10);
	
	push_q(q, 5);
	
	assert(pop_q(q) == 5);
	
	destroy_q(q);
}

void test_queue_is_empty(){
	printf("\ntest_queue_is_empty\n");
	
	queue *q = new_q();

	assert(is_empty_q(q) == TRUE);
	
	push_q(q, 10);
	
	assert(is_empty_q(q) == FALSE);
	
	push_q(q, 0);
	
	assert(is_empty_q(q) == FALSE);
	
	pop_q(q);
	pop_q(q);
	
	assert(is_empty_q(q) == TRUE);
	
	destroy_q(q);
}

void test_queue(){
	test_queue_push();
	test_queue_pop();
	test_queue_is_empty();
}
