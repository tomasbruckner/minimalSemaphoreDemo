#   Author: Tomas Bruckner
#   Date: 20.3.2018    
#   Description: 
#       Example of two processes sharing variables in C for Linux.
#
#		To run type in terminal:
#       	make run
#
#       If you are getting SIGSEGV, try:
#           rm /dev/shm/sem.shared_memory
#

CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic
LFLAGS=-lpthread
BIN=shared_memory
SOURCE=shared_memory.c

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(BIN) $(LFLAGS)

run: all
	./$(BIN)

clean:
	rm $(BIN)
