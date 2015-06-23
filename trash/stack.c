#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEAR "clear || cls"
#define SIZE 10
//pilha: metodos -> insert, search, erase, edit, pop


/**
 *
 *Foi convencionado que o indice de totalmente vazio é -1, assim como também o espaço vazio.
 *
**/


 /*

Foi convencionado que o indice de totalmente vazio é -1, assim como também o espaço vazio.

*/
typedef struct {
	int elements[SIZE];
	int last_index;
	int size;
} stack_struct;

//limpar stdin
void clear(void){
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}
//recebe uma string, imprime e faz uma pausa até capturar alguma tecla.
void pause(const char* string){
	printf("%s", string);
	clear();
}


//iniciar stack
void start(stack_struct *stack){
	int i;
	//convenção>todas posições do vetor iniciam com -1 e seu índice também;
	stack->last_index = -1;
	for(i = 0; i < SIZE; i++)
		stack->elements[i] = -1;
}

void random_values(stack_struct *stack){
	int i;
	time_t t;
	srand((unsigned) time(&t));

	for(i = 0; i < SIZE; i++)
		stack->elements[i] = rand() % 100;
	stack->last_index = i;
}

//versão optimizada e mais simples
void rearrange(stack_struct *stack){
	//ignorando espaços vazios e rearrajando vetor
	int i, j;
	for(i = 0, j = 0; i < SIZE; i++){
		if (stack->elements[i] != -1){
			stack->elements[j] = stack->elements[i];
			j++;
		}
	}
	//atribuindo o resto do vetor como vazio
	for(i = j; i < SIZE; i++) stack->elements[i] = -1;

	stack->last_index = j - 1;
}

void del(stack_struct *stack, int index){
	stack->elements[index] = -1;
	rearrange(stack);
}


//pop the last element on the list
int pop(stack_struct *stack){
	if(stack->last_index == -1)
		return -1;
	else
		del(stack, stack->last_index);

	printf("Pop Tail: %d\n", stack->elements[stack->last_index]);

	return 0;
}

int generate(const char *message){
	int num;
	puts(message);
	scanf("%d", &num);
	clear();

	return num;
}

void new_element(stack_struct *stack, int index){
	printf("Insert a value: ");
	scanf("%d", &stack->elements[index]);
	clear();
}

 
//insere um valor no final da stack;
int insert(stack_struct *stack){
	//se tiver cheia tal stack
	if (stack->last_index == SIZE -1)
		return -1;

	stack->last_index++;
	new_element(stack, stack->last_index);

	return 0;
}


int search(stack_struct *stack, int num){
	int i;
	
	for(i = 0; i < SIZE; i++)
		if(stack->elements[i] == num)
			return i;
	return -1;
}

int erase(stack_struct *stack, int num){
	int index = search(stack, num);

	if(index != -1)
		del(stack, index);
	else
		return -1;

	return index;
	
}

int edit(stack_struct *stack, int index){
	if(!(index >= 0 && index <= SIZE))
		return -1;

	new_element(stack, index);

	return 0;
}

void print_list(stack_struct *stack){
	//valores na stack:
	int i, value;
	printf("stack: [ ");
	for(i = 0; i < SIZE; i++){
		value = stack->elements[i];
		if (value != -1)
			printf(" (%d) ", stack->elements[i]);
		else
			printf(" () ");
	}
	printf("]\n");
}

void menu(stack_struct *stack){
	int command, status, num_key;
	do{	
		system(CLEAR);
		puts("Implementation of type stack in the class list!");
		printf("0.Exit\n1.Insert\n2.Pop\n3.PrintVector\n4.Search\n5.Edit\n6.Erase\n7.Rearrange\n8.RandomValues\n\n");
		printf("Type a command: ");
		scanf("%d", &command);
		clear();
		switch(command){
			case 1:
				status = insert(stack);
				if (status == -1) puts("Full stack!");
				break;
			case 2:
				status = pop(stack);
				if (status == -1) puts("Empty stack!");
				break;
			case 3:
				print_list(stack);
				break;
			case 4:
				num_key = generate("Search for: ");
				status = search(stack, num_key);
				if (status != -1)
					printf("Founded element %d on position %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 5:
				num_key = generate("Edit value in index: ");
				status = edit(stack, num_key);
				if(status == -1)
					printf("Index out of the range!\n");
				break;
			case 6:
				num_key = generate("Erase element: ");
				status = erase(stack, num_key);
				if (status != -1)
					printf("Deleted element %d on position %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 7:
				rearrange(stack);
				break;
			case 8:
				random_values(stack);
				break;
			case 0:
				printf("Leaving the universe...\n");
				break;
			default:
				printf("Command invalid, try again.!\n");
				break;
		}
		pause("Press enter to continue...");
	}while(command != 0);
}

int main(void){
	stack_struct stack;
	start(&stack);
	menu(&stack);

	return 0;
}