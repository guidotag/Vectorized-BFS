/*
 * Queue data structure.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"
#include "defines.h"

typedef struct queue{
	list *l;
} queue;

queue *new_q();

void push_q(queue *q, int e);

int pop_q(queue *q);

bool is_empty_q(queue *q);

void destroy_q(queue *q);

#endif
