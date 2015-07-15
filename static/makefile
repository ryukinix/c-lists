GCC = gcc
LFLAGS = -Wall -o

QUEUE_TARGET = static-queue
DEQUE_EXEC = static-deque
STACK_EXEC = static-stack

all: static-deque static-queue static-stack

static-deque:
	$(GCC) $(LFLAGS) $(DEQUE_EXEC) $(DEQUE_EXEC).c 

static-queue:
	$(GCC) $(LFLAGS) $(QUEUE_TARGET) $(QUEUE_TARGET).c

static-stack:
	$(GCC) $(LFLAGS) $(STACK_EXEC) $(STACK_EXEC).c 

clean:
	rm $(QUEUE_EXEC) $(DEQUE_EXEC) $(STACK_EXEC)