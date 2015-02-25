CC = gcc
ASM = nasm

CFLAGS = -O2 -Wall -std=c99 -pedantic #-Werror
ASMFLAGS = -f elf64 #macho64

BIN_DIR = ./bin
SRC_DIR = ./src
SRC_TEST_DIR = ./tests/src

BIN = bfs
MAIN = main.o
OBJS = bmatrix.o list.o bfs.o queue.o utils.o vectorized_bfs.o

BIN_TEST = tests
MAIN_TEST = main.o
OBJS_TEST = test_bmatrix.o test_list.o test_queue.o test_utils.o test_bfs.o

BIN_PATH = $(BIN_DIR)/$(BIN)
MAIN_PATH = $(SRC_DIR)/$(MAIN)
OBJS_PATH = $(addprefix $(SRC_DIR)/, $(OBJS))

BIN_TEST_PATH = $(BIN_DIR)/$(BIN_TEST)
MAIN_TEST_PATH = $(SRC_TEST_DIR)/$(MAIN_TEST)
OBJS_TEST_PATH = $(addprefix $(SRC_TEST_DIR)/, $(OBJS_TEST))

.PHONY: all clean bfs tests

all: bfs tests

bfs: $(MAIN_PATH) $(OBJS_PATH)
	$(CC) $^ -o $(BIN_PATH)
	
tests: $(OBJS_PATH) $(MAIN_TEST_PATH) $(OBJS_TEST_PATH)
	$(CC) $^ -o $(BIN_TEST_PATH)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -f $(MAIN_PATH)
	rm -f $(OBJS_PATH)
	rm -f $(BIN_PATH)
	rm -f $(OBJS_TEST_PATH)
	rm -f $(MAIN_TEST_PATH)
	rm -f $(BIN_TEST_PATH)
	
