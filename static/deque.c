#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEAR "clear || cls"
#define SIZE 10
//metodos > insert, search, erase, edit


/*

Foi convencionado que o indice de totalmente vazio é -1, assim como também o espaço vazio.

*/
typedef struct {
	int elements[SIZE];
	int last_index_l;
	int last_index_r;
	int size;
} deque_struct;

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


//iniciar deque
void start(deque_struct *deque){
	int i;
	//convenção>todas posições do vetor iniciam com -1 e seu índice também;
	deque->last_index = -1;
	for(i = 0; i < SIZE; i++)
		deque->elements[i] = -1;
}

void random_values(deque_struct *deque){
	int i;
	time_t t;
	srand((unsigned) time(&t));

	for(i = 0; i < SIZE; i++)
		deque->elements[i] = rand() % 100;
	deque->last_index = i;
}

//versão optimizada e mais simples
void rearrange(deque_struct *deque){
	//ignorando espaços vazios e rearrajando vetor
	int i, j;
	for(i = 0, j = 0; i < SIZE; i++){
		if (deque->elements[i] != -1){
			deque->elements[j] = deque->elements[i];
			j++;
		}
	}
	//atribuindo o resto do vetor como vazio
	for(i = j; i < SIZE; i++) deque->elements[i] = -1;

	deque->last_index = j - 1;
}

void del(deque_struct *deque, int index){
	deque->elements[index] = -1;
	rearrange(deque);
}


//step na deque
int step(deque_struct *deque){
	printf("Pop Head: %d\n", deque->elements[0]);
	

	if(deque->last_index == -1)
		return -1;
	else
		del(deque, 0);

	return 0;
}

int generate(const char *message){
	int num;
	puts(message);
	scanf("%d", &num);
	clear();

	return num;
}

void new_element(deque_struct *deque, int index){
	printf("Insert a value: ");
	scanf("%d", &deque->elements[index]);
	clear();
}

 
//insere um valor no final da deque;
int insert(deque_struct *deque){
	//se tiver cheia tal deque
	if (deque->last_index == SIZE -1)
		return -1;

	deque->last_index++;
	new_element(deque, deque->last_index);

	return 0;
}



int search(deque_struct *deque, int num){
	int i;
	
	for(i = 0; i < SIZE; i++)
		if(deque->elements[i] == num)
			return i;
	return -1;
}

int erase(deque_struct *deque, int num){
	int index = search(deque, num);

	if(index != -1)
		del(deque, index);
	else
		return -1;

	return index;
	
}

int edit(deque_struct *deque, int index){
	if(!(index >= 0 && index <= SIZE))
		return -1;

	new_element(deque, index);

	return 0;
}

void print_list(deque_struct *deque){
	//valores na deque:
	int i, value;
	printf("deque: [ ");
	for(i = 0; i < SIZE; i++){
		value = deque->elements[i];
		if (value != -1)
			printf(" (%d) ", deque->elements[i]);
		else
			printf(" () ");
	}
	printf("]\n");
}

void menu(deque_struct *deque){
	int command, status, num_key;
	do{	
		system(CLEAR);
		puts("Implementation of type deque_struct in the class list!");
		printf("0.Exit\n1.Insert\n2.Step\n3.PrintVector\n4.Search\n5.Edit\n6.Erase\n7.Rearrange\n8.RandomValues\n\n");
		printf("Type a command: ");
		scanf("%d", &command);
		clear();
		switch(command){
			case 1:
				status = insert(deque);
				if (status == -1) puts("Full deque_struct!");
				break;
			case 2:
				status = step(deque);
				if (status == -1) puts("Empty deque_struct!");
				break;
			case 3:
				print_list(deque);
				break;
			case 4:
				num_key = generate("Search for: ");
				status = search(deque, num_key);
				if (status != -1)
					printf("Encontrado elemento %d na posição %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 5:
				num_key = generate("Edit value in index: ");
				status = edit(deque, num_key);
				if(status == -1)
					printf("Index out of the range!\n");
				break;
			case 6:
				num_key = generate("Erase element: ");
				status = erase(deque, num_key);
				if (status != -1)
					printf("Deleted element %d on position %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 7:
				rearrange(deque);
				break;
			case 8:
				random_values(deque);
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
	deque_struct deque;
	start(&deque);
	menu(&deque);

	return 0;
}