CC = gcc
ASM = nasm

CFLAGS = -O2 -Wall -std=c99 -pedantic #-Werror
ASMFLAGS = -felf64 -g -F dwarf

BIN_DIR = bin/
SRC_DIR = src/
SRC_TEST_DIR = tests/src/

BIN = bfs
MAIN = main.o
OBJS = bmatrix.o list.o vectorized_bfs.o bfs.o queue.o utils.o

BIN_TEST = tests
MAIN_TEST = main.o
OBJS_TEST = test_bmatrix.o test_list.o test_queue.o test_utils.o test_bfs.o

BIN_W_DIR = $(BIN_DIR)$(BIN)
MAIN_W_DIR = $(SRC_DIR)$(MAIN)
OBJS_W_DIR = $(addprefix $(SRC_DIR), $(OBJS))

BIN_TEST_W_DIR = $(BIN_DIR)$(BIN_TEST)
MAIN_TEST_W_DIR = $(SRC_TEST_DIR)$(MAIN_TEST)
OBJS_TEST_W_DIR = $(addprefix $(SRC_TEST_DIR), $(OBJS_TEST))

.PHONY: all clean bfs tests

all: bfs tests

bfs: $(MAIN_W_DIR) $(OBJS_W_DIR)
	$(CC) $^ -o $(BIN_W_DIR)
	
tests: $(OBJS_W_DIR) $(MAIN_TEST_W_DIR) $(OBJS_TEST_W_DIR)
	$(CC) $^ -o $(BIN_TEST_W_DIR)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -f $(MAIN_W_DIR)
	rm -f $(OBJS_W_DIR)
	rm -f $(BIN_W_DIR)
	rm -f $(OBJS_TEST_W_DIR)
	rm -f $(MAIN_TEST_W_DIR)
	rm -f $(BIN_TEST_W_DIR)
	
