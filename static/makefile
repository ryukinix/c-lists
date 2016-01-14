GCC = gcc
LFLAGS = -Wall -o

QUEUE_TARGET = static-queue
DEQUE_TARGET = static-deque
STACK_TARGET = static-stack

all: static-deque static-queue static-stack

static-deque:
	@echo "Compiling static Deque"
	$(GCC) $(LFLAGS) $(DEQUE_TARGET).out $(DEQUE_TARGET).c
	@echo "Compiled with succesfull!"

static-queue:
	@echo "Compiling static Queue"
	$(GCC) $(LFLAGS) $(QUEUE_TARGET).out $(QUEUE_TARGET).c
	@echo "Compiled with succesfull!"

static-stack:
	@echo "Compiling static Stack"
	$(GCC) $(LFLAGS) $(STACK_TARGET).out $(STACK_TARGET).c
	@echo "Compiled with succesful!"

clean:
	rm -v *.out