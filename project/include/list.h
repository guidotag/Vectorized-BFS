/*
 * Doubly linked list data structure.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "utils.h"

typedef struct node_l{
	int e;
	struct node_l *next;
	struct node_l *prev;
} node_l;

typedef struct list{
	node_l *first;
	node_l *last;
} list;

list *new_l();

/*
 * Creates and returns a new list.
 */
int back_l(list *l);

/*
 * Appends a node at the front of the list.
 */
void append_front_l(list *l, int e);

/*
 * Prints the list.
 */
void print_l(list *l);

/*
 * Frees the memory used by the list. Note that it does not free
 * cell's memory.
 */
void destroy_l(list *l);

#endif
