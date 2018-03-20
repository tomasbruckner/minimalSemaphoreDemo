#   Author: Tomas Bruckner
#   Date: 20.3.2018    
#   Description: 
#       Example of two processes synchronized by two semaphores in C for Linux.
#
#		To run type in terminal:
#       	make run
#
#       If you are getting SIGSEGV, try:
#           rm /dev/shm/sem.semaphore_synchronization1 /dev/shm/sem.semaphore_synchronization2
#

CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic
LFLAGS=-lpthread
BIN=semaphore_synchronization
SOURCE=semaphore_synchronization.c

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(BIN) $(LFLAGS)

run: all
	./$(BIN)

clean:
	rm $(BIN)
