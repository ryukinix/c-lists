GCC = gcc
LFLAGS = -Wall -o

QUEUE_TARGET = dynamic-queue
DEQUE_TARGET = dynamic-deque
STACK_TARGET = dynamic-stack

all: dynamic-deque dynamic-queue dynamic-stack

dynamic-deque:
	$(GCC) $(LFLAGS) $(DEQUE_TARGET).out $(DEQUE_TARGET).c 

dynamic-queue:
	$(GCC) $(LFLAGS) $(QUEUE_TARGET).out $(QUEUE_TARGET).c

dynamic-stack:
	$(GCC) $(LFLAGS) $(STACK_TARGET).out $(STACK_TARGET).c 

clean:
	rm -v *.out