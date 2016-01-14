GCC = gcc
LFLAGS = -Wall -o

QUEUE_TARGET = dynamic-queue
DEQUE_TARGET = dynamic-deque
STACK_TARGET = dynamic-stack

all: dynamic-deque dynamic-queue dynamic-stack

dynamic-deque:
	@echo "Compiling dynamic Deque"
	$(GCC) $(LFLAGS) $(DEQUE_TARGET).out $(DEQUE_TARGET).c 
	@echo "Compiled with succesfull!"
dynamic-queue:
	@echo "Compiling dynamic Queue"
	$(GCC) $(LFLAGS) $(QUEUE_TARGET).out $(QUEUE_TARGET).c
	@echo "Compiled with succesfull!"
dynamic-stack:
	@echo "Compiling dynamic Stack"
	$(GCC) $(LFLAGS) $(STACK_TARGET).out $(STACK_TARGET).c 
	@echo "Compiled with succesful!"
clean:
	rm -v *.out