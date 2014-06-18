#include "../include/test_list.h"

void test_list_append_front(){
	printf("\ntest_list_append_front\n");
	list *l = new_l();
	
	append_front_l(l, -3);
	append_front_l(l, 8);
	append_front_l(l, 0);
	append_front_l(l, 21);
	append_front_l(l, -5);
	
	print_l(l);
	
	destroy_l(l);
}

void test_list_back(){
	printf("\ntest_list_back\n");
	
	list *l = new_l();
	
	append_front_l(l, -3);
	append_front_l(l, 8);
	append_front_l(l, 0);
	append_front_l(l, 21);
	append_front_l(l, -5);
	
	assert(back_l(l) == -3);
	assert(back_l(l) == 8);
	assert(back_l(l) == 0);
	
	append_front_l(l, 17);
	
	assert(back_l(l) == 21);
	assert(back_l(l) == -5);
	assert(back_l(l) == 17);
	
	append_front_l(l, 0);
	
	assert(back_l(l) == 0);
	
	destroy_l(l);
}

void test_list(){
	test_list_append_front();
	test_list_back();
}
