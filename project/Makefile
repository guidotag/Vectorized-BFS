CC=gcc
ASM=nasm

CFLAGS=-O2 -Wall -std=c99 -pedantic #-Werror
ASMFLAGS=-felf64 -g -F dwarf

BIN_DIR=bin/
SRC_DIR=src/
SRC_TEST_DIR=tests/src/

BIN=bfs
OBJ_MAIN=main.o
OBJS=bmatrix.o list.o vectorized_bfs.o bfs.o queue.o utils.o

BIN_TEST=tests
OBJ_MAIN_TEST=main.o
OBJS_TEST=test_bmatrix.o test_list.o test_queue.o test_utils.o test_bfs.o

OBJ_MAIN_W_DIR=$(SRC_DIR)$(OBJ_MAIN)
OBJS_W_DIR=$(addprefix $(SRC_DIR), $(OBJS))

OBJ_MAIN_TEST_W_DIR=$(SRC_TEST_DIR)$(OBJ_MAIN_TEST)
OBJS_TEST_W_DIR=$(addprefix $(SRC_TEST_DIR), $(OBJS_TEST))

BIN_W_DIR=$(BIN_DIR)$(BIN)
BIN_TEST_W_DIR=$(BIN_DIR)$(BIN_TEST)

.PHONY: all clean run bfs tests

all: bfs tests

bfs: $(OBJ_MAIN_W_DIR) $(OBJS_W_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_W_DIR)
	
tests: $(OBJS_W_DIR) $(OBJ_MAIN_TEST_W_DIR) $(OBJS_TEST_W_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_TEST_W_DIR)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
run: bfs
	./bin/bfs
	
clean:
	rm -f $(OBJ_MAIN_W_DIR)
	rm -f $(OBJS_W_DIR)
	rm -f $(BIN_W_DIR)
	rm -f $(OBJS_TEST_W_DIR)
	rm -f $(OBJ_MAIN_TEST_W_DIR)
	rm -f $(BIN_TEST_W_DIR)
	
