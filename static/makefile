GCC = gcc
LFLAGS = -Wall -o

QUEUE_TARGET = static-queue
DEQUE_TARGET = static-deque
STACK_TARGET = static-stack

all: static-deque static-queue static-stack

static-deque:
	$(GCC) $(LFLAGS) $(DEQUE_TARGET).out $(DEQUE_TARGET).c 

static-queue:
	$(GCC) $(LFLAGS) $(QUEUE_TARGET).out $(QUEUE_TARGET).c

static-stack:
	$(GCC) $(LFLAGS) $(STACK_TARGET).out $(STACK_TARGET).c 

clean:
	rm -v *.out